#include <iostream>
#include <random>
#include <cmath>
#include "../l1/implot-master/implot.h"
#include "../l1/implot-master/implot_internal.h"

int main()
{

    int bar_data[11];
    float x_data[1000];
    float y_data[1000];

    ImGui::Begin("My Window");
    if (ImPlot::BeginPlot("My Plot"))
    {
        ImPlot::PlotBars("My Bar Plot", bar_data, 11);
        ImPlot::PlotLine("My Line Plot", x_data, y_data, 1000);
        ImPlot::EndPlot();
    }
    ImGui::End();
}