#pragma once

/**
 * A structure for containing data of a minimal to maximal range of values in a
 * 2D field.
 */
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
    GenotypeData class contains all the data needed for constructing a genotype.
*/
template<typename GeometryData>
class GenotypeData{
    public:
        
        /**
         * Contains all the data needed for constructing a genotype.
         * 
         * @param num_geometries (int) Number of geometries
         * @param numeric_range (Range) The range in whitch the geometries can get created
         * @param geo_data (GeometryData) class containing all relevant data to the geomety thats created.
         */
        GenotypeData(int num_geometries, Range numeric_range, GeometryData geo_data);
        ~GenotypeData() = default;
        GenotypeData() = default;

        /**
         * @returns (int) Number of geometries.
         */
        int GetNumberOfGeometries();

        /**
         * @returns (Range) The defined numeric range.
         */
        Range GetRange();

        /**
         * @returns (GeometryData) The geometry data.
         */
        GeometryData GetGeometryData();

        /**
         * @param num_geometries Set number of geometries.
         */
        void SetNumberOfGeometries(int num_geometries);

        /**
         * @param range Set range of geometries.
         */
        void SetRange(Range range);

        /**
         * @param geo_data Set geometry data.
         */
        void SetGeometryData(GeometryData geo_data);

    private:
        int m_geometries_number{};
        Range m_numeric_range;
        GeometryData m_geometry_data;
};