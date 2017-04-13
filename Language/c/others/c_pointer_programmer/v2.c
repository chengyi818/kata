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

struct pair {
     void *first;
     void *second;
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
struct pair *pair_for_double_type(double x, double y)
{
    struct pair *ret = malloc(sizeof(struct pair));
    double *first = malloc(sizeof(double));
    double *second = malloc(sizeof(double));
    *first = x;
    *second = y;
    ret->first = first;
    ret->second = first;

    return ret;

}

struct chain_node *create_chain_node(void)
{
    struct pair *left_center = pair_for_double_type(1.0, 1.0);
    double *left_radius = malloc(sizeof(double));
    *left_radius = 0.5;
    struct pair *left_hole = malloc(sizeof(struct pair));
    left_hole->first = left_center;
    left_hole->second = left_radius;

    struct pair *right_center = pair_for_double_type(9.0, 1.0);
    double *right_radius = malloc(sizeof(double));
    *right_radius = 0.5;
    struct pair *right_hole = malloc(sizeof(struct pair));
    right_hole->first = right_center;
    right_hole->second = right_radius;

    struct pair *holes = malloc(sizeof(struct pair));
    holes->first = left_hole;
    holes->second = right_hole;
    struct pair *body = pair_for_double_type(10.0, 1.0);
    struct pair *shape = malloc(sizeof(struct pair));
    shape->first = body;
    shape->second = holes;

    struct chain_node *ret = malloc(sizeof(struct chain_node));
    ret->prev = NULL;
    ret->next = NULL;
    ret->shape = shape;

    return ret;
}
