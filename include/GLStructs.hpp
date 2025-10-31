#ifndef GLSTRUCTS_HPP
# define GLSTRUCTS_HPP

# include <type_traits>

struct s_vec2 { float x, y; };
struct s_vec3 { float x, y, z; };
struct s_vec4 { float x, y, z, w; };
struct s_mat4 { float m[4][4]; };
struct s_quat { float w, x, y, z; };

template<typename T> struct is_vec2 : std::false_type {};
template<typename T> struct is_vec3 : std::false_type {};
template<typename T> struct is_vec4 : std::false_type {};
template<typename T> struct is_mat4 : std::false_type {};
template<typename T> struct is_quat : std::false_type {};

template<> struct is_vec2<s_vec2> : std::true_type {};
template<> struct is_vec3<s_vec3> : std::true_type {};
template<> struct is_vec4<s_vec4> : std::true_type {};
template<> struct is_mat4<s_mat4> : std::true_type {};
template<> struct is_quat<s_quat> : std::true_type {};

template<class> struct always_false : std::false_type {};

#endif