#ifndef VEC2_H
#define VEC2_H

typedef struct s_vec2 {
	double	x;
	double	y;
} t_vec2;

// Add together two t_vec2
t_vec2	add(t_vec2 a, t_vec2 b);
t_vec2	rot(t_vec2 a, t_vec2 b);
t_vec2	mul(t_vec2 a, t_vec2 b);

#endif // VEC2_H
