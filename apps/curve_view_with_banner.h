#ifndef APPS_CURVE_VIEW_WITH_BANNER_H
#define APPS_CURVE_VIEW_WITH_BANNER_H

#include <escher.h>
#include "curve_view.h"
#include "banner_view.h"

class CurveViewWithBanner : public CurveView {
public:
  CurveViewWithBanner(CurveViewWindow * curveViewWindow = nullptr, float topMarginFactor = 0.0f,
    float rightMarginFactor = 0.0f, float bottomMarginFactor = 0.0f, float leftMarginFactor = 0.0f);
  virtual void reloadSelection() = 0;
  void reload() override;
  bool isMainViewSelected();
  void selectMainView(bool mainViewSelected);
protected:
  void layoutSubviews() override;
  bool m_mainViewSelected;
  virtual BannerView * bannerView() = 0;
private:
  constexpr static KDCoordinate k_bannerHeight = 30;
  int numberOfSubviews() const override;
  View * subviewAtIndex(int index) override;
};

#endif
