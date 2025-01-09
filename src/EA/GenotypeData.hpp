#pragma once

struct Range{
    Range() = default;
    Range(int x_min, int x_max, int y_min, int y_max):
    m_x_min(x_min),
    m_x_max(x_max),
    m_y_min(y_min),
    m_y_max(y_max)
    {

    }

    bool operator==(const Range& p) const{
        bool min_x = m_x_min == p.m_x_min;
        bool max_x = m_x_max == p.m_x_max;
        bool max_y = m_y_max == p.m_y_max;
        bool min_y = m_y_min == p.m_y_min;
        
        return min_x && max_x && max_y && min_y;
    }

    int m_x_min;
    int m_x_max;
    int m_y_min;
    int m_y_max;
}; 

/*
    GeometryData needed to have information on specific geometry parameter.
*/
template<typename GeometryData>
class GenotypeData{
    public:
        GenotypeData() = default;
        GenotypeData(int num_geometries, Range numeric_range, GeometryData geo_data);
        ~GenotypeData() = default;

        int GetNumberOfGeometries();
        Range GetRange();
        GeometryData GetGeometryData();

        void SetNumberOfGeometries(int num_geometries);
        void SetRange(Range range);
        void SetGeometryData(GeometryData geo_data);

    private:
        int m_geometries_number{};
        Range m_numeric_range;
        GeometryData m_geometry_data;
};