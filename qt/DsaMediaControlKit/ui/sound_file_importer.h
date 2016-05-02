#ifndef UI_SOUND_FILE_IMPORTER_H
#define UI_SOUND_FILE_IMPORTER_H

#include <QWidget>
#include <QPushButton>

namespace UI {

class SoundFileImporter : public QWidget
{
    Q_OBJECT
public:
    explicit SoundFileImporter(QWidget *parent = 0);

    void parseFolder(QUrl const& url);

signals:

public slots:

private slots:
    void onBrowseButtonClicked(bool);

private:
    void initWidgets();
    void initLayout();

    QPushButton* browse_button_;

};

} // namespace UI

#endif // UI_SOUND_FILE_IMPORTER_H
