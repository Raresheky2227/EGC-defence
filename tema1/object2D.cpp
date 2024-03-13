#include "object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(-length, length, 0), color),
        VertexFormat(corner + glm::vec3(-length, -length, 0), color),
        VertexFormat(corner + glm::vec3(length, -length, 0), color),
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    float height,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(length, height, 2), color),
        VertexFormat(corner + glm::vec3(-length, height, 2), color),
        VertexFormat(corner + glm::vec3(-length, -height, 2), color),
        VertexFormat(corner + glm::vec3(length, -height, 2), color),
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateStar(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;
    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(1.0f * 20, 0.0f * 20, 1), color),
        VertexFormat(corner + glm::vec3(0.309f * 20, 0.951f * 20, 1), color),
        VertexFormat(corner + glm::vec3(-0.809f * 20, 0.588f * 20, 1), color),
        VertexFormat(corner + glm::vec3(-0.809f * 20, -0.588f * 20, 1), color),
        VertexFormat(corner + glm::vec3(0.309f * 20, -0.951f * 20, 1), color),
        VertexFormat(corner + glm::vec3(-0.45f * 20, 0.0f * 20, 1), color),
        VertexFormat(corner + glm::vec3(-0.1f * 20, -0.44f * 20, 1), color),
        VertexFormat(corner + glm::vec3(-0.1f * 20, 0.44f * 20, 1), color),

    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 6, 2,
                                          3, 7, 0,
                                          4, 5, 1 };

    if (!fill) {
        star->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    star->InitFromData(vertices, indices);
    return star;

}

Mesh* object2D::CreateHex(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color2,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(20, 0, 1), glm::vec3(1, 0, 0)),
        VertexFormat(corner + glm::vec3(10, 1.73 * 10, 1), glm::vec3(1, 1, 0)),
        VertexFormat(corner + glm::vec3(-10, 1.73 * 10, 1), glm::vec3(0, 1, 0)),
        VertexFormat(corner + glm::vec3(-20, 0, 1), glm::vec3(0, 1, 1)),
        VertexFormat(corner + glm::vec3(-10, -1.73 * 10, 1), glm::vec3(0, 0, 1)),
        VertexFormat(corner + glm::vec3(10, -1.73 * 10, 1), glm::vec3(1, 0, 1)),

        VertexFormat(corner + glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)),

        VertexFormat(corner + glm::vec3(40, 0, 0), color2),
        VertexFormat(corner + glm::vec3(20, 1.73 * 20, 0), color2),
        VertexFormat(corner + glm::vec3(-20, 1.73 * 20, 0), color2),
        VertexFormat(corner + glm::vec3(-40, 0, 0), color2),
        VertexFormat(corner + glm::vec3(-20, -1.73 * 20, 0), color2),
        VertexFormat(corner + glm::vec3(20, -1.73 * 20, 0), color2),

        VertexFormat(corner + glm::vec3(0, 0, 0), glm::vec3(1, 1, 1)),
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 6,
                                          1, 2, 6,
                                          2, 3, 6,
                                          3, 4, 6,
                                          4, 5, 6,
                                          5, 0, 6,
                                          7, 8, 13,
                                          8, 9, 13,
                                          9, 10, 13,
                                          10, 11, 13,
                                          11, 12, 13,
                                          12, 7, 13};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}


Mesh* object2D::CreateRhombus(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, 45, 2), color),
        VertexFormat(corner + glm::vec3(14, 0, 2), color),
        VertexFormat(corner + glm::vec3(0, -45, 2), color),
        VertexFormat(corner + glm::vec3(-14, 0, 2), color),
        VertexFormat(corner + glm::vec3(0, 8, 2), color),
        VertexFormat(corner + glm::vec3(0, -8, 2), color),
        VertexFormat(corner + glm::vec3(35, 8, 2), color),
        VertexFormat(corner + glm::vec3(35, -8, 2), color),
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                          0, 3, 2,
                                          4, 5, 7,
                                          4, 6, 7};

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* object2D::CreateHeart(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(1.5, 1.5, 0), color),
        VertexFormat(corner + glm::vec3(3, 0, 0), color),
        VertexFormat(corner + glm::vec3(0, -4, 0), color),
        VertexFormat(corner + glm::vec3(-3, 0, 0), color),
        VertexFormat(corner + glm::vec3(-1.5, 1.5, 0), color),
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2,
                                          4, 5, 0,
                                          4, 3, 2 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}
