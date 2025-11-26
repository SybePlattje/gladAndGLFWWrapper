#ifndef GLSTRUCTS_HPP
# define GLSTRUCTS_HPP

# include <type_traits>

struct s_vec2 { float x, y; };
struct s_vec3 { float x, y, z; };
struct s_vec4 { float x, y, z, w; };
struct s_mat4
{
    s_vec4 cols[4];

    float& operator()(int row, int col)
    {
        return ((float*)&cols[col])[row];
    }

    const float& operator()(int row, int col) const
    {
        return ((float*)&cols[col])[row];
    }

    s_vec4& operator[](int col)
    {
        return cols[col];
    }

    const s_vec4& operator[](int col) const
    {
        return cols[col];
    }
};
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

#if __has_include(<glm/glm.hpp>)
    #include <glm/glm.hpp>
    #include <glm/gtc/matrix_transform.hpp>
    #include <glm/gtc/type_ptr.hpp>

    template<> struct is_vec2<glm::vec2> : std::true_type {};
    template<> struct is_vec3<glm::vec3> : std::true_type {};
    template<> struct is_vec4<glm::vec4> : std::true_type {};
    template<glm::qualifier Q>
    struct is_mat4<glm::mat<4, 4, float, Q>> : std::true_type {};
    template<glm::qualifier Q>
    struct is_quat<glm::qua<float, Q>> : std::true_type {};

#endif

template<class> struct always_false : std::false_type {};

#endif