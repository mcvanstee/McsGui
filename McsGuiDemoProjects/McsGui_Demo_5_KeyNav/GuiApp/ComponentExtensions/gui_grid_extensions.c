#include "gui_grid_extensions.h"


Grid_s *gui_addPageButtonGrid(View_s *p_view)
{
    Rectangle_s *p_backgroundRect = rectangle_new();
    rectangle_initFillPosSize(
        p_backgroundRect, theme_getBackgroundColor(),
        STYLE_VIEW_X, STYLE_VIEW_Y,
        STYLE_DISPLAY_WIDTH, STYLE_VIEW_HEIGHT);
    view_addComponent(p_view, p_backgroundRect);

    Grid_s *p_grid = grid_newInit();
    grid_setColumns(p_grid, 3);
    grid_setRows(p_grid, 2);
    grid_setColumnSpacing(p_grid, 10);
    grid_setRowSpacing(p_grid, 10);
    base_addNewInitAnchor(p_grid);
    anchor_setCenterInParent(p_grid, p_backgroundRect);
    view_addComponent(p_view, p_grid);

    return p_grid;
}

PageButton_s *gui_addPageButton(Grid_s *p_grid, const file_key_e icon, const file_key_e text, void (*onPressed)(void))
{
    PageButton_s *p_pageButton = page_btn_new();
    page_btn_initIconText(p_pageButton, icon, text, onPressed);
    grid_addComponent(p_grid, p_pageButton);

    if (p_grid->componentCount == 2)
    {
        PageButton_s *p_topLeftBtn = (PageButton_s*)p_grid->base.p_childList;
        keynav_right(p_topLeftBtn, p_pageButton);
        keynav_left(p_pageButton, p_topLeftBtn);
    }
    else if (p_grid->componentCount == 3)
    {
        PageButton_s *p_topCenterBtn = (PageButton_s*)grid_getComponent(p_grid, 0, 1);
        keynav_right(p_topCenterBtn, p_pageButton);
        keynav_left(p_pageButton, p_topCenterBtn);
    }
    else if (p_grid->componentCount == 4)
    {
        PageButton_s *p_topLeftBtn = (PageButton_s*)p_grid->base.p_childList;
        keynav_down(p_topLeftBtn, p_pageButton);
        keynav_up(p_pageButton, p_topLeftBtn);
    }
    else if (p_grid->componentCount == 5)
    {
        PageButton_s *p_topCenterBtn = (PageButton_s*)grid_getComponent(p_grid, 0, 1);
        PageButton_s *p_downLeftBtn = (PageButton_s*)grid_getComponent(p_grid, 1, 0);
        keynav_right(p_downLeftBtn, p_pageButton);
        keynav_left(p_pageButton, p_downLeftBtn);
        keynav_down(p_topCenterBtn, p_pageButton);
        keynav_up(p_pageButton, p_topCenterBtn);
    }
    else if (p_grid->componentCount == 6)
    {
        PageButton_s *p_topRightBtn = (PageButton_s*)grid_getComponent(p_grid, 0, 2);
        PageButton_s *p_downCenterBtn = (PageButton_s*)grid_getComponent(p_grid, 1, 1);
        keynav_right(p_downCenterBtn, p_pageButton);
        keynav_left(p_pageButton, p_downCenterBtn);
        keynav_down(p_topRightBtn, p_pageButton);
        keynav_up(p_pageButton, p_topRightBtn);
    }
    else
    {
    }

    return p_pageButton;
}

