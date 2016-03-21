#include <stdio.h>
#include <stdlib.h>

struct chain_node {
    struct chain_node *prev;
    struct chain_node *next;
    void *shape;
};

struct point {
    double x;
    double y;
};

struct rectangle {
    double width;
    double height;
};

struct circle {
    struct point *center;
    double radius;
};

struct chain_node_shape {
    struct rectangle *body;
    struct circle *hole[2];
};

struct point *create_point(double x, double y);
struct circle *create_circle(struct point *center, double radius);
struct rectangle *create_rectangle(double w, double h);
struct chain_node_shape *create_chain_node_shape(struct circle *c1, struct circle *c2, struct rectangle *rect);
struct chain_node *create_chain_node(void);

int main()
{
    struct chain_node *head = create_chain_node();
    struct chain_node *tail = head;
    int i = 0;
    for(i =0; i<1000; i++)
    {
        struct chain_node *new_tail = create_chain_node();
        new_tail->prev = tail;
        tail->next = new_tail;
        tail = new_tail;
    }
    tail->next = head;
    head->prev = tail;
}


struct point *create_point(double x, double y)
{
    struct point *ret = malloc(sizeof(struct point));
    ret->y = y;
    ret->x = x;
    return ret;
}

struct circle *create_circle(struct point *center, double radius)
{
    struct circle *ret = malloc(sizeof(struct circle));
    ret->center = center;
    ret->radius = radius;

    return ret;
}

struct rectangle *create_rectangle(double w, double h)
{
     struct rectangle *ret = malloc(sizeof(struct rectangle));
     ret->height = h;
     ret->width = w;

     return ret;
}

struct chain_node_shape *create_chain_node_shape(struct circle *c1, struct circle *c2, struct rectangle *rect)
{
    struct chain_node_shape *ret= malloc(sizeof(struct chain_node_shape));
    ret->body = rect;
    ret->hole[0] = c1;
    ret->hole[1] = c2;

    return ret;
}

struct chain_node *create_chain_node(void)
{
    double radius = 0.5;
    double left_x = 1.0;
    double left_y = 1.0;
    struct point *left_center = create_point(left_x, left_y);
    struct circle *left_hole = create_circle(left_center, radius);

    double right_x = 9.0;
    double right_y = 1.0;
    struct point *right_center = create_point(right_x, right_y);
    struct circle *right_hole = create_circle(right_center, radius);
    struct rectangle *body = create_rectangle(10.0, 2.0);

    struct chain_node *ret = malloc(sizeof(struct chain_node));
    ret->prev = NULL;
    ret->next = NULL;

    ret->shape = create_chain_node_shape(left_hole, right_hole, body);

    return ret;
}
