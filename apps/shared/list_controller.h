#ifndef SHARED_LIST_CONTROLLER_H
#define SHARED_LIST_CONTROLLER_H

#include <escher.h>
#include "function_store.h"
#include "list_parameter_controller.h"
#include "new_function_cell.h"

namespace Shared {

class ListController : public ViewController, public HeaderViewDelegate, public TableViewDataSource {
public:
  ListController(Responder * parentResponder, FunctionStore * functionStore, HeaderViewController * header, const char * text);
  View * view() override;
  int numberOfColumns() override;
  KDCoordinate columnWidth(int i) override;
  KDCoordinate cumulatedWidthFromIndex(int i) override;
  KDCoordinate cumulatedHeightFromIndex(int j) override;
  int indexFromCumulatedWidth(KDCoordinate offsetX) override;
  int indexFromCumulatedHeight(KDCoordinate offsetY) override;
  int typeAtLocation(int i, int j) override;
  HighlightCell * reusableCell(int index, int type) override;
  int reusableCellCount(int type) override;
  void willDisplayCellAtLocation(HighlightCell * cell, int i, int j) override;
  void didBecomeFirstResponder() override;
  bool handleEvent(Ion::Events::Event event) override;
  void viewWillAppear() override;
protected:
  static constexpr KDCoordinate k_emptyRowHeight = 50;
  StackViewController * stackController() const;
  void configureFunction(Shared::Function * function);
  SelectableTableView m_selectableTableView;
  FunctionStore * m_functionStore;
private:
  static constexpr KDCoordinate k_functionNameWidth = 65;
  Responder * tabController() const;
  virtual ListParameterController * parameterController() = 0;
  virtual int maxNumberOfRows() = 0;
  virtual HighlightCell * titleCells(int index) = 0;
  virtual HighlightCell * expressionCells(int index) = 0;
  virtual void willDisplayTitleCellAtIndex(HighlightCell * cell, int j) = 0;
  virtual void willDisplayExpressionCellAtIndex(HighlightCell * cell, int j) = 0;
  EvenOddCell m_emptyCell;
  NewFunctionCell m_addNewFunction;
};

}

#endif
