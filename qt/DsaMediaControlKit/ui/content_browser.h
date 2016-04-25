#ifndef UI_CONTENT_BROWSER_H
#define UI_CONTENT_BROWSER_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QUrl>

namespace UI {

class ContentBrowser : public QWidget
{
    Q_OBJECT
public:
    ContentBrowser(QWidget* parent = 0);
    ~ContentBrowser();

    QUrl const& getLastUrl() const;

signals:
    void urlChanged(QUrl const&);

private slots:
    void browseClicked(bool);

private:
    void initWidgets();
    void initLayout();

    QPushButton* browse_button_;
    QLineEdit* file_edit_;
    QUrl last_url_;
};

} // namespace UI

#endif // UI_CONTENT_BROWSER_H
