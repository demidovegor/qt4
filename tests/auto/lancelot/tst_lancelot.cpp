/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the test suite of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** No Commercial Usage
** This file contains pre-release code and may not be distributed.
** You may use this file in accordance with the terms and conditions
** contained in the Technology Preview License Agreement accompanying
** this package.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights.  These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**
**
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include <QtTest/QtTest>
#include <paintcommands.h>
#include <QPainter>
#include <QLibraryInfo>
#include <baselineprotocol.h>
#include <QHash>

#ifndef QT_NO_OPENGL
#include <QtOpenGL>
#endif

#ifndef SRCDIR
#define SRCDIR "."
#endif

class tst_Lancelot : public QObject
{
Q_OBJECT

public:
    tst_Lancelot();

    static bool simfail;

private:
    enum GraphicsEngine {
        Raster = 0,
        OpenGL = 1
    };

    bool setupTestSuite(const QStringList& blacklist);
    void runTestSuite(GraphicsEngine engine, QImage::Format format);
    ImageItem render(const ImageItem &item, GraphicsEngine engine, QImage::Format format);
    void paint(QPaintDevice *device, const QStringList &script, const QString &filePath);

    BaselineProtocol proto;
    ImageItemList baseList;
    QHash<QString, QStringList> scripts;
    bool dryRunMode;
    QString scriptsDir;

private slots:
    void initTestCase();
    void cleanupTestCase() {}

    void testRasterARGB32PM_data();
    void testRasterARGB32PM();
    void testRasterRGB32_data();
    void testRasterRGB32();
    void testRasterRGB16_data();
    void testRasterRGB16();

#ifndef QT_NO_OPENGL
    void testOpenGL_data();
    void testOpenGL();
#endif
};

bool tst_Lancelot::simfail = false;

tst_Lancelot::tst_Lancelot()
{
}

void tst_Lancelot::initTestCase()
{
    // Check and setup the environment. We treat failures because of test environment
    // (e.g. script files not found) as just warnings, and not QFAILs, to avoid false negatives
    // caused by environment or server instability

#if defined(Q_OS_SOMEPLATFORM)
    QSKIP("This test is not supported on this platform.", SkipAll);
#endif
    if (!proto.connect(QLatin1String("tst_Lancelot"), &dryRunMode))
        QSKIP(qPrintable(proto.errorMessage()), SkipAll);

#if defined(USE_RUNTIME_DIR)
    scriptsDir = QCoreApplication::applicationDirPath() + "/scripts/";
#else
    scriptsDir = SRCDIR "/scripts/";
#endif
    QDir qpsDir(scriptsDir);
    QStringList files = qpsDir.entryList(QStringList() << QLatin1String("*.qps"), QDir::Files | QDir::Readable);
    if (files.isEmpty()) {
        QWARN("No qps script files found in " + qpsDir.path().toLatin1());
        QSKIP("Aborted due to errors.", SkipAll);
    }

    baseList.resize(files.count());
    ImageItemList::iterator it = baseList.begin();
    foreach(const QString& fileName, files) {
        QFile file(scriptsDir + fileName);
        file.open(QFile::ReadOnly);
        QByteArray cont = file.readAll();
        scripts.insert(fileName, QString::fromLatin1(cont).split(QLatin1Char('\n'), QString::SkipEmptyParts));
        it->itemName = fileName;
        it->itemChecksum = qChecksum(cont.constData(), cont.size());
        it++;
    }
}


void tst_Lancelot::testRasterARGB32PM_data()
{
    QStringList localBlacklist;
    if (!setupTestSuite(localBlacklist))
        QSKIP("Communication with baseline image server failed.", SkipAll);
}


void tst_Lancelot::testRasterARGB32PM()
{
    runTestSuite(Raster, QImage::Format_ARGB32_Premultiplied);
}


void tst_Lancelot::testRasterRGB32_data()
{
    QStringList localBlacklist;
    if (!setupTestSuite(localBlacklist))
        QSKIP("Communication with baseline image server failed.", SkipAll);
}


void tst_Lancelot::testRasterRGB32()
{
    runTestSuite(Raster, QImage::Format_RGB32);
}


void tst_Lancelot::testRasterRGB16_data()
{
    QStringList localBlacklist;
    if (!setupTestSuite(localBlacklist))
        QSKIP("Communication with baseline image server failed.", SkipAll);
}


void tst_Lancelot::testRasterRGB16()
{
    runTestSuite(Raster, QImage::Format_RGB16);
}


#ifndef QT_NO_OPENGL
void tst_Lancelot::testOpenGL_data()
{
    QStringList localBlacklist = QStringList() << QLatin1String("rasterops.qps");
    if (!setupTestSuite(localBlacklist))
        QSKIP("Communication with baseline image server failed.", SkipAll);
}


void tst_Lancelot::testOpenGL()
{
    bool ok = false;
    QGLWidget glWidget;
    if (glWidget.isValid() && glWidget.format().directRendering()
        && ((QGLFormat::openGLVersionFlags() & QGLFormat::OpenGL_Version_2_0)
            || (QGLFormat::openGLVersionFlags() & QGLFormat::OpenGL_ES_Version_2_0))
        && QGLFramebufferObject::hasOpenGLFramebufferObjects())
    {
        glWidget.makeCurrent();
        if (!QByteArray((const char *)glGetString(GL_VERSION)).contains("Mesa"))
            ok = true;
    }
    if (ok)
        runTestSuite(OpenGL, QImage::Format_RGB32);
    else
        QSKIP("System under test does not meet preconditions for GL testing. Skipping.", SkipAll);
}
#endif


bool tst_Lancelot::setupTestSuite(const QStringList& blacklist)
{
    QTest::addColumn<ImageItem>("baseline");

    ImageItemList itemList(baseList);
    if (!proto.requestBaselineChecksums(QTest::currentTestFunction(), &itemList)) {
        QWARN(qPrintable(proto.errorMessage()));
        return false;
    }

    foreach(const ImageItem& item, itemList) {
        if (!blacklist.contains(item.itemName))
            QTest::newRow(item.itemName.toLatin1()) << item;
    }
    return true;
}


void tst_Lancelot::runTestSuite(GraphicsEngine engine, QImage::Format format)
{
    QFETCH(ImageItem, baseline);

    if (baseline.status == ImageItem::IgnoreItem)
        QSKIP("Blacklisted by baseline server.", SkipSingle);

    ImageItem rendered = render(baseline, engine, format);
    static int consecutiveErrs = 0;
    if (rendered.image.isNull()) {    // Assume an error in the test environment, not Qt
        QWARN("Error: Failed to render image.");
        if (++consecutiveErrs < 3) {
            QSKIP("Aborted due to errors.", SkipSingle);
        } else {
            consecutiveErrs = 0;
            QSKIP("Too many errors, skipping rest of testfunction.", SkipAll);
        }
    } else {
        consecutiveErrs = 0;
    }


    if (baseline.status == ImageItem::BaselineNotFound) {
        proto.submitNewBaseline(rendered, 0);
        QSKIP("Baseline not found; new baseline created.", SkipSingle);
    }

    if (!baseline.imageChecksums.contains(rendered.imageChecksums.at(0))) {
            QByteArray serverMsg;
            if (!proto.submitMismatch(rendered, &serverMsg))
                serverMsg = "Failed to submit mismatching image to server.";
            if (dryRunMode)
                qDebug() << "Dryrun mode, ignoring detected mismatch." << serverMsg;
            else
                QFAIL("Rendered image differs from baseline. Report:\n   " + serverMsg);
    }
}


ImageItem tst_Lancelot::render(const ImageItem &item, GraphicsEngine engine, QImage::Format format)
{
    ImageItem res = item;
    res.imageChecksums.clear();
    res.image = QImage();
    QString filePath = scriptsDir + item.itemName;
    QStringList script = scripts.value(item.itemName);

    if (engine == Raster) {
        QImage img(800, 800, format);
        paint(&img, script, QFileInfo(filePath).absoluteFilePath()); // eh yuck (filePath stuff)
        res.image = img;
        res.imageChecksums.append(ImageItem::computeChecksum(img));
#ifndef QT_NO_OPENGL
    } else if (engine == OpenGL) {
        QGLWidget glWidget;
        if (glWidget.isValid()) {
            glWidget.makeCurrent();
            QGLFramebufferObjectFormat fboFormat;
            fboFormat.setSamples(16);
            fboFormat.setAttachment(QGLFramebufferObject::CombinedDepthStencil);
            QGLFramebufferObject fbo(800, 800, fboFormat);
            paint(&fbo, script, QFileInfo(filePath).absoluteFilePath()); // eh yuck (filePath stuff)
            res.image = fbo.toImage().convertToFormat(format);
            res.imageChecksums.append(ImageItem::computeChecksum(res.image));
        }
#endif
    }

    return res;
}

void tst_Lancelot::paint(QPaintDevice *device, const QStringList &script, const QString &filePath)
{
    QPainter p(device);
    PaintCommands pcmd(script, 800, 800);
    //pcmd.setShouldDrawText(false);
    pcmd.setType(ImageType);
    pcmd.setPainter(&p);
    pcmd.setFilePath(filePath);
    pcmd.runCommands();
    p.end();

    if (simfail) {
        QPainter p2(device);
        p2.setPen(QPen(QBrush(Qt::cyan), 3, Qt::DashLine));
        p2.drawLine(200, 200, 600, 600);
        p2.drawLine(600, 200, 200, 600);
        simfail = false;
    }
}

#define main rmain
QTEST_MAIN(tst_Lancelot)
#undef main

int main(int argc, char *argv[])
{
    char *fargv[20];
    int fargc = 0;
    for (int i = 0; i < qMin(argc, 19); i++) {
        if (!qstrcmp(argv[i], "-simfail"))
            tst_Lancelot::simfail = true;
        else
            fargv[fargc++] = argv[i];
    }
    fargv[fargc] = 0;
    return rmain(fargc, fargv);
}

#include "tst_lancelot.moc"
