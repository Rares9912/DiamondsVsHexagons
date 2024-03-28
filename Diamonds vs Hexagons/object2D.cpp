#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquares(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 firstColor,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, firstColor),
        VertexFormat(corner + glm::vec3(length, 0, -1), firstColor),
        VertexFormat(corner + glm::vec3(length, length, -1), firstColor),
        VertexFormat(corner + glm::vec3(0, length, -1), firstColor)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    float width,
    glm::vec3 firstColor,
    bool fill) 
{

    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, 0, -1), firstColor),
        VertexFormat(corner + glm::vec3(width, 0, -1), firstColor),
        VertexFormat(corner + glm::vec3(width, length, -1), firstColor),
        VertexFormat(corner + glm::vec3(0, length, -1), firstColor)
    };
    
    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = 
    {   
        0,
        1, 
        2, 
        3 
    };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    } else {
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;

}

Mesh* object2D::CreateDiamond(
    const std::string &name,
    glm::vec3 bottomCorner,
    float length,
    glm::vec3 firstColor,
    bool fill) 
{

    glm::vec3 corner = bottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, 0, 1), firstColor),
        VertexFormat(corner + glm::vec3(-length/2, length, 1), firstColor),
        VertexFormat(corner + glm::vec3(0, 2 * length, 1), firstColor),
        VertexFormat(corner + glm::vec3(0.4 * length, 1.1 * length, 1), firstColor),
        VertexFormat(corner + glm::vec3(length, 1.1 * length, 1), firstColor),
        VertexFormat(corner + glm::vec3(length, 0.9 * length, 1), firstColor),
        VertexFormat(corner + glm::vec3(0.4 * length, 0.9 * length, 1), firstColor),
        VertexFormat(corner + glm::vec3(length/2, length, 1), firstColor)
    };

    Mesh* diamond = new Mesh(name);
    std::vector<unsigned int> indices = 
    {   
        0,
        1, 
        2, 

        2,
        7,
        0,

        3,
        4,
        5,

        5,
        6,
        3
    };

    if (!fill) {
        diamond->SetDrawMode(GL_LINE_LOOP);
    }

    diamond->InitFromData(vertices, indices);
    return diamond;

}

Mesh* object2D::CreateHexagon(
    const std::string &name,
    glm::vec3 origin,
    float length,
    glm::vec3 firstColor,
    glm::vec3 secondColor,
    bool fill) 
{

    glm::vec3 corner = origin;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, 0, 0), firstColor),
        VertexFormat(corner + glm::vec3(-length, 0, 0), firstColor),
        VertexFormat(corner + glm::vec3(-length/2, length * sqrt(3) / 2, 0), firstColor),
        VertexFormat(corner + glm::vec3(length/2, length * sqrt(3) / 2, 0), firstColor),
        VertexFormat(corner + glm::vec3(length, 0, 0), firstColor),
        VertexFormat(corner + glm::vec3(length/2, -length * sqrt(3) / 2, 0), firstColor),
        VertexFormat(corner + glm::vec3(-length/2, -length * sqrt(3) / 2, 0), firstColor),

        VertexFormat(corner + glm::vec3(0, 0, 1), firstColor),
        VertexFormat(corner + glm::vec3(-length/1.5, 0, 1), secondColor),
        VertexFormat(corner + glm::vec3(-length/3, (length/1.5) * sqrt(3) / 2, 1), secondColor),
        VertexFormat(corner + glm::vec3(length/3, (length/1.5) * sqrt(3) / 2, 1), secondColor),
        VertexFormat(corner + glm::vec3(length/1.5, 0, 1), secondColor),
        VertexFormat(corner + glm::vec3(length/3, (-length/1.5) * sqrt(3) / 2, 1), secondColor),
        VertexFormat(corner + glm::vec3(-length/3, (-length/1.5) * sqrt(3) / 2, 1), secondColor)
        
    };

    Mesh* hexagon = new Mesh(name);

    std::vector<unsigned int> indices = 
    {   
        0,
        1, 
        2,

        0,
        2,
        3,

        0,
        3,
        4,

        0,
        4,
        5,

        0,
        5,
        6,

        0,
        6,
        1,

        8,
        9,
        10,

        8,
        10,
        11,

        8,
        11,
        12,

        8,
        12,
        13,

        8,
        13,
        14,

        8,
        14,
        9
    };

    if (!fill) {
        hexagon->SetDrawMode(GL_LINE_LOOP);
    } 

    hexagon->InitFromData(vertices, indices);
    return hexagon;

}

Mesh* object2D::CreateStar(
    const std::string &name,
    glm::vec3 origin,
    float length,
    glm::vec3 color,
    bool fill) 
{
    glm::vec3 corner = origin;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, 0, 0), color),
        VertexFormat(corner + glm::vec3(0, -length, 0), color),
        VertexFormat(corner + glm::vec3(-2.5 * length, length, 0), color),
        VertexFormat(corner + glm::vec3(2.5 * length, length, 0), color),
        VertexFormat(corner + glm::vec3(-1.5 * length, -2 * length, 0), color),
        VertexFormat(corner + glm::vec3(1.5 * length, -2 * length, 0), color),
        VertexFormat(corner + glm::vec3(0, 2.5 * length, 0), color)
    };

    Mesh* star = new Mesh(name);

    std::vector<unsigned int> indices = 
    {   
        1,
        2,
        3,

        4,
        6,
        1,

        5,
        6,
        1
        
       
    };

    if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP);
    } 

    star->InitFromData(vertices, indices);
    return star;
}
