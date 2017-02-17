#ifndef GRAPH_GRAPH_INITIALISATION_PARAMETER_CONTROLLER_H
#define GRAPH_GRAPH_INITIALISATION_PARAMETER_CONTROLLER_H

#include <escher.h>
#include "../../shared/interactive_curve_view_range.h"

namespace Graph {

class InitialisationParameterController : public ViewController, public SimpleListViewDataSource {
public:
  InitialisationParameterController(Responder * parentResponder, Shared::InteractiveCurveViewRange * graphRange);
  View * view() override;
  const char * title() const override;
  bool handleEvent(Ion::Events::Event event) override;
  void didBecomeFirstResponder() override;
  int numberOfRows() override;
  KDCoordinate cellHeight() override;
  HighlightCell * reusableCell(int index) override;
  int reusableCellCount() override;
  void willDisplayCellForIndex(HighlightCell * cell, int index) override;
private:
  constexpr static int k_totalNumberOfCells = 4;
  PointerTableCell m_cells[k_totalNumberOfCells];
  SelectableTableView m_selectableTableView;
  Shared::InteractiveCurveViewRange * m_graphRange;
};

}

#endif
