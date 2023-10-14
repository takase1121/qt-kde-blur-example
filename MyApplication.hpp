#include "qpushbutton.h"
#include <QApplication>
#include <QObject>
#include <KWayland/Client/registry.h>
#include <KWayland/Client/blur.h>

class MyApplication: public QObject {
    Q_OBJECT

public:
    MyApplication(int argc, char **argv);

    int run();

public slots:
    void onBlurAnnounced(quint32 name, quint32 version);

private:
    QApplication m_application;
    QPushButton m_button;
    KWayland::Client::Compositor *m_compositor;
    KWayland::Client::Registry m_registry;
    KWayland::Client::BlurManager *m_blurManager;
    KWayland::Client::Blur *m_blur;
};