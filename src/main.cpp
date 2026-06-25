#include <Geode/Geode.hpp>
#include <Geode/modify/CCEGLView.hpp>

using namespace geode::prelude;

class $modify(CCEGLView) {
    void setFrameSize(float width, float height) {
        auto w = static_cast<float>(Mod::get()->getSettingValue<int64_t>("width"));
        auto h = static_cast<float>(Mod::get()->getSettingValue<int64_t>("height"));

        // If the settings are specified, apply them, ignoring the game's attempts to reset the size
        if (w > 0 && h > 0) {
            CCEGLView::setFrameSize(w, h);
            auto director = CCDirector::sharedDirector();
            director->getWinSize();
            CCEGLView::setViewPortInPoints(0, 0, w, h);
        }
        else {
            // If the setting is 0, we simply skip the standard method
            CCEGLView::setFrameSize(width, height);
        }
    }
};

$execute{
    listenForSettingChanges<int64_t>("width", +[](int64_t) {
        auto gl = CCEGLView::sharedOpenGLView();
        if (gl) gl->setFrameSize(0, 0); // Let's start the update
    });
    listenForSettingChanges<int64_t>("height", +[](int64_t) {
        auto gl = CCEGLView::sharedOpenGLView();
        if (gl) gl->setFrameSize(0, 0);
    });
}