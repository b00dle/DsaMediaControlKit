#include "custom_media_player.h"
#include <random>

CustomMediaPlayer::CustomMediaPlayer(QObject* parent)
    : QMediaPlayer(parent)
    , current_content_index_(0)
    , delay_flag_(false)
    , delay_(0)
    , delay_timer_(0)
{
    delay_timer_ = new QTimer(this);
    connect(delay_timer_, SIGNAL(timeout()),
            this, SLOT(delayIsOver()));

}

void CustomMediaPlayer::play()
{

    Playlist::Playlist* playlist = getCustomPlaylist();
    if(playlist){
        Playlist::Settings* settings = playlist->getSettings();

        setVolume(settings->volume);
        // if delay interval is turned on
        if (settings->order == Playlist::PlayOrder::ORDERED){
            if (settings->loop_flag){
                playlist->setPlaybackMode(QMediaPlaylist::Loop);

            }else if (!settings->loop_flag){
                playlist->setPlaybackMode(QMediaPlaylist::Sequential);

            }
        } else if (settings->order == Playlist::PlayOrder::SHUFFLE){
            playlist->setPlaybackMode(QMediaPlaylist::Random);
            int index = getRandomIntInRange(0,playlist->mediaCount()-1);
            playlist->setCurrentIndex(index);
            //for (playlist->mediaCount())


        } else if (settings->order == Playlist::PlayOrder::WEIGTHED){
            // TO DO implement weighted
            QMediaPlayer::pause();

        }

        if (settings->interval_flag){
            delay_ = getRandomIntInRange(settings->min_delay_interval,
                                         settings->max_delay_interval);
            delay_flag_ = true;

            QMediaPlayer::play();


            playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
        } else {
            delay_flag_ = false;
            delay_ = 0;
            QMediaPlayer::play();
        }
        qDebug() << "Playing Index: "<<playlist->currentIndex();
    }
}

void CustomMediaPlayer::setPlaylist(Playlist::Playlist *playlist)
{
    connect(playlist, SIGNAL(currentIndexChanged(int)),
            this, SLOT(currentMediaIndexChanged(int)) );

    connect(playlist, SIGNAL(changedSettings()),
            this, SLOT(mediaSettingsChanged()) );

    QMediaPlayer::setPlaylist(playlist);
}

void CustomMediaPlayer::delayIsOver()
{
    delay_timer_->stop();
    play();
}

int CustomMediaPlayer::getRandomIntInRange(int min, int max)
{
    std::random_device rd;     // only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(min,max); // guaranteed unbiased
    return uni(rng);
}

void CustomMediaPlayer::currentMediaIndexChanged(int position)
{
    current_content_index_ = position;
    if (delay_flag_){
        delay_timer_->start(delay_*1000);
    }
}

void CustomMediaPlayer::mediaSettingsChanged()
{
    Playlist::Settings* settings = getCustomPlaylist()->getSettings();
    setVolume(settings->volume);
    if (settings->interval_flag){
        delay_flag_ = true;
        delay_ = getRandomIntInRange(settings->min_delay_interval,
                                     settings->max_delay_interval);
    } else {
        delay_flag_ = false;
        delay_ = 0;
    }

    if (settings->order == Playlist::PlayOrder::ORDERED){

    } else if (settings->order == Playlist::PlayOrder::SHUFFLE){
        getCustomPlaylist()->setPlaybackMode(QMediaPlaylist::Random);
    } else if (settings->order == Playlist::PlayOrder::WEIGTHED){
        qDebug() << "weigthed not implemented yet";
    }

}


Playlist::Playlist *CustomMediaPlayer::getCustomPlaylist() const
{

    Playlist::Playlist* pl = qobject_cast<Playlist::Playlist*>( playlist() );
    if(pl){
        return pl;
    } else {
        return nullptr;
    }
}

