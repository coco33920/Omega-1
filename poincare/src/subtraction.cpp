extern "C" {
#include <assert.h>
#include <stdlib.h>
}

#include <poincare/subtraction.h>
#include "layout/horizontal_layout.h"
#include "layout/string_layout.h"
#include "layout/parenthesis_layout.h"

Expression * Subtraction::cloneWithDifferentOperands(Expression** newOperands,
    int numberOfOperands, bool cloneOperands) const {
  assert(newOperands != nullptr);
  assert(numberOfOperands == 2);
  return new Subtraction(newOperands, cloneOperands);
}

float Subtraction::approximate(Context& context) const {
  return m_operands[0]->approximate(context) - m_operands[1]->approximate(context);
}

Expression::Type Subtraction::type() const {
  return Expression::Type::Subtraction;
}

ExpressionLayout * Subtraction::createLayout(DisplayMode displayMode) const {
  ExpressionLayout** children_layouts = (ExpressionLayout **)malloc(3*sizeof(ExpressionLayout *));
  children_layouts[0] = m_operands[0]->createLayout(displayMode);
  char string[2] = {'-', '\0'};
  children_layouts[1] = new StringLayout(string, 1);
  children_layouts[2] = m_operands[1]->type() == Type::Opposite ? new ParenthesisLayout(m_operands[1]->createLayout(displayMode)) : m_operands[1]->createLayout(displayMode);
  return new HorizontalLayout(children_layouts, 3);
}

Expression * Subtraction::evaluateOnMatrixAndFloat(Matrix * m, Float * a, Context& context) const {
  Expression * operands[m->numberOfRows() * m->numberOfColumns()];
  for (int i = 0; i < m->numberOfRows() * m->numberOfColumns(); i++) {
    operands[i] = new Float(m->operand(i)->approximate(context) - a->approximate(context));
  }
  return new Matrix(operands, m->numberOfRows() * m->numberOfColumns(), m->numberOfColumns(), m->numberOfRows(), false);
}

Expression * Subtraction::evaluateOnFloatAndMatrix(Float * a, Matrix * m, Context& context) const {
  Expression * operands[m->numberOfRows() * m->numberOfColumns()];
  for (int i = 0; i < m->numberOfRows() * m->numberOfColumns(); i++) {
    operands[i] = new Float(a->approximate(context) - m->operand(i)->approximate(context));
  }
  return new Matrix(operands, m->numberOfRows() * m->numberOfColumns(), m->numberOfColumns(), m->numberOfRows(), false);
}

Expression * Subtraction::evaluateOnMatrices(Matrix * m, Matrix * n, Context& context) const {
  if (m->numberOfColumns() != n->numberOfColumns() || m->numberOfRows() != n->numberOfRows()) {
    return nullptr;
  }
  Expression * operands[m->numberOfRows() * m->numberOfColumns()];
  for (int i = 0; i < m->numberOfRows() * m->numberOfColumns(); i++) {
    if (!m->operand(i)->approximate(context) || !n->operand(i)->approximate(context)) {
      return nullptr;
    }
    operands[i] = new Float(m->operand(i)->approximate(context) - n->operand(i)->approximate(context));
  }
  return new Matrix(operands, m->numberOfRows() * m->numberOfColumns(), m->numberOfColumns(), m->numberOfRows(), false);
}
