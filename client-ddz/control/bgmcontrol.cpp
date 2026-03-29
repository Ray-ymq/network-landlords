#include "bgmcontrol.h"
#include "playhand.h"

#include <QAudioOutput>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QRandomGenerator>
#include <QTimer>

BGMControl::BGMControl(QObject *parent) : QObject(parent)
{
    // QMediaPlayer* player = new QMediaPlayer;
    // player->setAudioOutput(audioOutput);
    // player->setSource(QUrl::fromLocalFile("/Users/me/Music/coolsong.mp3"));
    // audioOutput->setVolume(50);
    // player->play();

    for(int i=0; i<5; ++i)
    {
        QMediaPlayer* player = new QMediaPlayer(this);
        // QMediaPlaylist* list = new QMediaPlaylist(this);
        if(i<2 || i == 4)
        {
            // list->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
            player->setLoops(QMediaPlayer::Once);
        }
        else if(i == 2)
        {
            // list->setPlaybackMode(QMediaPlaylist::Loop);
            player->setLoops(QMediaPlayer::Infinite);
        }
        // player->setPlaylist(list);
        // player->setVolume(100);
        QAudioOutput* audioOutput = new QAudioOutput;
        player->setAudioOutput(audioOutput);
        audioOutput->setVolume(100);
        m_players.push_back(player);
        // m_lists.push_back(list);
    }
    initPlayList();
}

void BGMControl::initPlayList()
{
    QStringList list;
    list << "Man" << "Woman" << "BGM" << "Other" << "Ending";

    // 读json配置文件
    QFile file(":/conf/playList.json");
    file.open(QFile::ReadOnly);
    QByteArray json = file.readAll();
    file.close();
    // 解析从文件中读出的json数据
    QJsonDocument doc = QJsonDocument::fromJson(json);
    QJsonObject obj = doc.object();

    for(int i=0; i<list.size(); ++i)
    {
        QString prefix = list.at(i);
        QJsonArray array = obj.value(prefix).toArray();
        QVector<QString> mp3Lists;
        // 初始化多媒体播放列表
        for(int j=0; j<array.size(); ++j)
        {
            // m_lists[i]->addMedia(QMediaContent(QUrl(array.at(j).toString())));
            mp3Lists.append(array.at(j).toString());
        }
        m_lists.append(mp3Lists);
    }
}

void BGMControl::startBGM(int volume)
{
    // m_lists[2]->setCurrentIndex(0);
    // m_players[2]->setVolume(volume);
    // m_players[2]->play();
    m_players[2]->audioOutput()->setVolume(volume);
    m_players[2]->setSource(QUrl(m_lists[2].at(0)));
    m_players[2]->play();
}

void BGMControl::stopBGM()
{
    m_players[2]->stop();
}

// 玩家下注了没有?
// 玩家的性别?
// 什么时候播放什么样的音频文件
void BGMControl::playerRobLordMusic(int point, RoleSex sex, bool isFirst)
{
    int index = sex == Man ? 0 : 1;
    QString mp3 = QString();
    if(isFirst && point > 0)
    {
        mp3 = m_lists[index].at(Order);
    }
    else if(point == 0)
    {
        if(isFirst)
        {
            mp3 = m_lists[index].at(NoOrder);
        }
        else
        {
            mp3 = m_lists[index].at(NoRob);
        }
    }
    else if(point == 2)
    {
        mp3 = m_lists[index].at(Rob1);
    }
    else if(point == 3)
    {
        mp3 = m_lists[index].at(Rob2);
    }
    m_players[index]->setSource(QUrl(mp3));
    m_players[index]->play();
}

void BGMControl::playCardMusic(Cards cards, bool isFirst, RoleSex sex)
{
    // 得到播放列表
    int index = sex == Man ? 0 : 1;
    // QMediaPlaylist* list = m_lists[index];
    QVector<QString> list = m_lists.at(index);
    QString mp3 = QString();

    Card::CardPoint pt = Card::CardPoint::Card_Begin;
    // 取出牌型 然后进行判断
    PlayHand hand(cards);
    PlayHand::HandType type = hand.getHandType();
    if(type == PlayHand::Hand_Single || type == PlayHand::Hand_Pair || type == PlayHand::Hand_Triple)
    {
        pt = cards.takeRandomCard().point();
    }
    int number = 0;
    switch(type)
    {
    // 单牌
    case PlayHand::Hand_Single:
        number = pt - 1;
        break;
    // 对牌
    case PlayHand::Hand_Pair:
        number = pt - 1 + 15;
        break;
    // 三张点数相同的牌
    case PlayHand::Hand_Triple:
        number = pt - 1 + 15 + 13;
        break;
    // 三带一
    case PlayHand::Hand_Triple_Single:
        number = ThreeBindOne;
        break;
    // 三带二
    case PlayHand::Hand_Triple_Pair:
        number = ThreeBindPair;
        break;
    // 飞机
    case PlayHand::Hand_Plane:
    // 飞机带两个单
    case PlayHand::Hand_Plane_Two_Single:
    // 飞机带两个对儿
    case PlayHand::Hand_Plane_Two_Pair:
        number = Plane;
        break;
    // 连对
    case PlayHand::Hand_Seq_Pair:
        number = SequencePair;
        break;
    // 顺子
    case PlayHand::Hand_Seq_Single:
        number = Sequence;
        break;
    // 炸弹
    case PlayHand::Hand_Bomb:
        number = Bomb;
        break;
    // 王炸
    case PlayHand::Hand_Bomb_Jokers:
        number = JokerBomb;
        break;
    // 炸弹带一对儿
    case PlayHand::Hand_Bomb_Pair:
    // 炸弹带两单
    case PlayHand::Hand_Bomb_Two_Single:
    // 王炸带一对儿
    case PlayHand::Hand_Bomb_Jokers_Pair:
    // 王炸带两单
    case PlayHand::Hand_Bomb_Jokers_Two_Single:
        number = FourBindTwo;

    default:
        break;
    }

    if(!isFirst && (number >= Plane && number <= FourBindTwo))
    {
        mp3 = list.at(MoreBiger1 + QRandomGenerator::global()->bounded(2));
    }
    else
    {
        mp3 = list.at(number);
    }
    // 播放音乐
    m_players[index]->setSource(QUrl(mp3));
    m_players[index]->play();
    if(number == Bomb || number == JokerBomb)
    {
        playAssistMusic(BombVoice);
    }
    if(number == Plane)
    {
        playAssistMusic(PlaneVoice);
    }
}

void BGMControl::playLastMusic(CardType type, RoleSex sex)
{
    // 1. 玩家的性别
    int index = sex == Man ? 0 : 1;
    // 2. 找到播放列表
    QVector<QString> list = m_lists[index];
    if(m_players[index]->playbackState() == QMediaPlayer::StoppedState)
    {
        QString mp3 = list.at(type);
        m_players[index]->setSource(QUrl(mp3));
        m_players[index]->play();
    }
    else
    {
        QTimer::singleShot(1500, this, [=](){
            QString mp3 = list.at(type);
            m_players[index]->setSource(QUrl(mp3));
            m_players[index]->play();
        });
    }
}

void BGMControl::playPassMusic(RoleSex sex)
{
    // 1. 玩家的性别
    int index = sex == Man ? 0 : 1;
    // 2. 找到播放列表
    QVector<QString> list = m_lists[index];
    // 3. 找到要播放的音乐
    int random = QRandomGenerator::global()->bounded(4);
    QString mp3 = list.at(Pass1 + random);
    m_players[index]->setSource(QUrl(mp3));
    // 4. 播放音乐
    m_players[index]->play();
}

void BGMControl::playAssistMusic(AssistMusic type)
{
    int loopsMode;
    // QMediaPlaylist::PlaybackMode mode;
    if(type == Dispatch)
    {
        // 循环播放
        loopsMode = QMediaPlayer::Infinite;
    }
    else
    {
        // 单曲播放一次
        loopsMode = QMediaPlayer::Once;
    }
    // 2. 找到播放列表
    QVector<QString> list = m_lists[3];
    // 3. 找到要播放的音乐
    m_players[3]->setSource(list.at(type));
    m_players[3]->setLoops(loopsMode);
    // list->setPlaybackMode(mode);
    // 4. 播放音乐
    m_players[3]->play();
}

void BGMControl::stopAssistMusic()
{
    m_players[3]->stop();
}

void BGMControl::playEndingMusic(bool isWin)
{
    QString mp3 = QString();
    if(isWin)
    {
        mp3 = m_lists[4].at(0);
    }
    else
    {
        mp3 = m_lists[4].at(1);
    }
    m_players[4]->setSource(mp3);
    m_players[4]->play();
}
