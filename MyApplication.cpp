#include "MyApplication.hpp"
#include "KWayland/Client/blur.h"
#include "KWayland/Client/connection_thread.h"
#include "KWayland/Client/registry.h"
#include "KWayland/Client/surface.h"
#include "KWayland/Client/compositor.h"
#include "KWayland/Client/region.h"
#include "qglobal.h"
#include "qgraphicseffect.h"
#include "qnamespace.h"
#include "qobject.h"
#include <iostream>
#include <QGraphicsOpacityEffect>

MyApplication::MyApplication(int argc, char **argv): m_application(argc, argv) {
    m_button.setText("Press me");
    m_button.resize(250, 250);
    m_button.setWindowTitle("wow");
    m_button.show();

    m_button.setAttribute(Qt::WA_TranslucentBackground, true);

    m_compositor = KWayland::Client::Compositor::fromApplication(&m_application);
    auto connection = KWayland::Client::ConnectionThread::fromApplication(&m_application);
    QObject::connect(&m_registry, &KWayland::Client::Registry::blurAnnounced, this, &MyApplication::onBlurAnnounced);
    m_registry.create(connection);
    m_registry.setup();
}

int MyApplication::run() {
    return m_application.exec();
}

void MyApplication::onBlurAnnounced(quint32 name, quint32 version) {
    m_blurManager = m_registry.createBlurManager(name, version);
    auto surface = KWayland::Client::Surface::fromWindow(m_button.windowHandle());
    m_button.visibleRegion();
    m_blur = m_blurManager->createBlur(surface);
    m_blur->setRegion(m_compositor->createRegion(m_button.visibleRegion()).get());
    std::cout << "got manager!" << std::endl;
    std::cout << "blur " << m_blur << std::endl;
}

