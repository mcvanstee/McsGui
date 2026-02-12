#include "gui_grid_extensions.h"


Grid_s *gui_addPageButtonGrid(View_s *p_view)
{
    Rectangle_s *p_rect = rectangle_newInit();
    rectangle_showBorderOnly(p_rect, true);
    rectangle_setBorderThickness(p_rect, 13);
    rectangle_setBorderColor(p_rect, theme_getBackgroundColor());
    base_setDimensions(&p_rect->base, STYLE_DISPLAY_WIDTH, 216);
    base_setPosition(&p_rect->base, 0, 42);
    view_addComponent(p_view, p_rect);

    Grid_s *p_grid = grid_newInit();
    grid_setColumns(p_grid, 3);
    grid_setRows(p_grid, 2);
    grid_setColumnSpacing(p_grid, 10);
    grid_setRowSpacing(p_grid, 10);
    base_setBackground(p_grid, theme_getBackgroundColor());
    base_setTransparent(p_grid, false);
    base_addNewInitAnchor(&p_grid->base);
    anchor_setCenterInParent(p_grid, p_rect);
    view_addComponent(p_view, p_grid);

    return p_grid;
}

PageButton_s *gui_addPageButton(Grid_s *p_grid, const file_key_e icon, const file_key_e text, void (*onPressed)(void))
{
    PageButton_s *p_pageButton = page_btn_new();
    page_btn_initIconText(p_pageButton, icon, text, onPressed);
    grid_addComponent(p_grid, p_pageButton);

    return p_pageButton;
}
