// Auto generated from tools/makeassets.py

static const unsigned char DATA_shaders_atmosphere_glsl[2636] __attribute__((aligned(4))) =
    "/* Stellarium Web Engine - Copyright (c) 2018 - Noctua Software Ltd\n"
    " *\n"
    " * This program is licensed under the terms of the GNU AGPL v3, or\n"
    " * alternatively under a commercial licence.\n"
    " *\n"
    " * The terms of the AGPL v3 license can be found in the main directory of this\n"
    " * repository.\n"
    " */\n"
    "\n"
    "#ifdef GL_ES\n"
    "precision mediump float;\n"
    "#endif\n"
    "\n"
    "uniform highp float u_atm_p[12];\n"
    "uniform highp vec3  u_sun;\n"
    "uniform highp float u_tm[3]; // Tonemapping koefs.\n"
    "\n"
    "varying lowp    vec4        v_color;\n"
    "\n"
    "#ifdef VERTEX_SHADER\n"
    "\n"
    "attribute highp   vec4       a_pos;\n"
    "attribute highp   vec3       a_sky_pos;\n"
    "attribute highp   float      a_luminance;\n"
    "\n"
    "vec3 xyy_to_srgb(highp vec3 xyy)\n"
    "{\n"
    "    highp vec3 xyz;\n"
    "    highp vec3 rgb;\n"
    "    const highp mat3 xyz_to_rgb = mat3(3.2406, -0.9689, 0.0557,\n"
    "                                      -1.5372, 1.8758, -0.2040,\n"
    "                                      -0.4986, 0.0415, 1.0570);\n"
    "    xyz = vec3(xyy[0] * xyy[2] / xyy[1], xyy[2],\n"
    "               (1.0 - xyy[0] - xyy[1]) * xyy[2] / xyy[1]);\n"
    "    rgb = xyz_to_rgb * xyz;\n"
    "    return pow(rgb, vec3(1.0 / 2.2));\n"
    "}\n"
    "\n"
    "float tonemap(float lw)\n"
    "{\n"
    "    // Logarithmic tonemapping, same as in tonemapper.c\n"
    "    // Assumes u_tm[2] == 1.\n"
    "    return log(1.0 + u_tm[0] * lw) / log(1.0 + u_tm[0] * u_tm[1]);\n"
    "}\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec3 xyy;\n"
    "    float cos_gamma, cos_gamma2, gamma, cos_theta;\n"
    "    vec3 p = a_sky_pos;\n"
    "\n"
    "    gl_Position = a_pos;\n"
    "\n"
    "    p[2] = abs(p[2]); // Mirror below horizon.\n"
    "    cos_gamma = dot(p, u_sun);\n"
    "    cos_gamma2 = cos_gamma * cos_gamma;\n"
    "    gamma = acos(cos_gamma);\n"
    "    cos_theta = p[2];\n"
    "\n"
    "    xyy.x = ((1. + u_atm_p[0] * exp(u_atm_p[1] / cos_theta)) *\n"
    "             (1. + u_atm_p[2] * exp(u_atm_p[3] * gamma) +\n"
    "              u_atm_p[4] * cos_gamma2)) * u_atm_p[5];\n"
    "    xyy.y = ((1. + u_atm_p[6] * exp(u_atm_p[7] / cos_theta)) *\n"
    "             (1. + u_atm_p[8] * exp(u_atm_p[9] * gamma) +\n"
    "              u_atm_p[10] * cos_gamma2)) * u_atm_p[11];\n"
    "    xyy.z = a_luminance;\n"
    "\n"
    "    // Scotopic vision adjustment with blue shift (xy = 0.25, 0.25)\n"
    "    // Algo inspired from Stellarium.\n"
    "    if (xyy.z < 3.9) {\n"
    "        float s, v;\n"
    "        // s: ratio between scotopic and photopic vision.\n"
    "        s = smoothstep(0.0, 1.0, (log(xyy.z) / log(10.) + 2.) / 2.6);\n"
    "        xyy.x = mix(0.25, xyy.x, s);\n"
    "        xyy.y = mix(0.25, xyy.y, s);\n"
    "        v = xyy.z * (1.33 * (1. + xyy.y / xyy.x + xyy.x *\n"
    "                            (1. - xyy.x - xyy.y)) - 1.68);\n"
    "        xyy.z = 0.4468 * (1. - s) * v + s * xyy.z;\n"
    "    }\n"
    "\n"
    "    xyy.z = max(0.0, tonemap(xyy.z));\n"
    "    v_color = vec4(clamp(xyy_to_srgb(xyy), 0.0, 1.0), 1.0);\n"
    "}\n"
    "\n"
    "#endif\n"
    "#ifdef FRAGMENT_SHADER\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = v_color;\n"
    "}\n"
    "\n"
    "#endif\n"
    "";

ASSET_REGISTER(shaders_atmosphere_glsl, "shaders/atmosphere.glsl", DATA_shaders_atmosphere_glsl, false)

static const unsigned char DATA_shaders_blit_glsl[796] __attribute__((aligned(4))) =
    "/* Stellarium Web Engine - Copyright (c) 2018 - Noctua Software Ltd\n"
    " *\n"
    " * This program is licensed under the terms of the GNU AGPL v3, or\n"
    " * alternatively under a commercial licence.\n"
    " *\n"
    " * The terms of the AGPL v3 license can be found in the main directory of this\n"
    " * repository.\n"
    " */\n"
    "\n"
    "uniform highp   vec4        u_color;\n"
    "uniform mediump sampler2D   u_tex;\n"
    "\n"
    "varying highp   vec2        v_tex_pos;\n"
    "varying lowp    vec4        v_color;\n"
    "\n"
    "#ifdef VERTEX_SHADER\n"
    "\n"
    "attribute highp     vec4    a_pos;\n"
    "attribute mediump   vec2    a_tex_pos;\n"
    "attribute lowp      vec3    a_color;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = a_pos;\n"
    "    v_tex_pos = a_tex_pos;\n"
    "    v_color = vec4(a_color, 1.0) * u_color;\n"
    "}\n"
    "\n"
    "#endif\n"
    "#ifdef FRAGMENT_SHADER\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = texture2D(u_tex, v_tex_pos) * v_color;\n"
    "}\n"
    "\n"
    "#endif\n"
    "";

ASSET_REGISTER(shaders_blit_glsl, "shaders/blit.glsl", DATA_shaders_blit_glsl, false)

static const unsigned char DATA_shaders_blit_tag_glsl[810] __attribute__((aligned(4))) =
    "/* Stellarium Web Engine - Copyright (c) 2018 - Noctua Software Ltd\n"
    " *\n"
    " * This program is licensed under the terms of the GNU AGPL v3, or\n"
    " * alternatively under a commercial licence.\n"
    " *\n"
    " * The terms of the AGPL v3 license can be found in the main directory of this\n"
    " * repository.\n"
    " */\n"
    "\n"
    "uniform lowp    vec4        u_color;\n"
    "uniform mediump sampler2D   u_tex;\n"
    "\n"
    "varying mediump vec2        v_tex_pos;\n"
    "varying lowp    vec4        v_color;\n"
    "\n"
    "#ifdef VERTEX_SHADER\n"
    "\n"
    "attribute highp     vec4 a_pos;\n"
    "attribute mediump   vec2 a_tex_pos;\n"
    "attribute lowp      vec3 a_color;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = a_pos;\n"
    "    v_tex_pos = a_tex_pos;\n"
    "    v_color = vec4(a_color, 1.0) * u_color;\n"
    "}\n"
    "\n"
    "#endif\n"
    "#ifdef FRAGMENT_SHADER\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = v_color;\n"
    "    gl_FragColor.a *= texture2D(u_tex, v_tex_pos).r;\n"
    "}\n"
    "\n"
    "#endif\n"
    "";

ASSET_REGISTER(shaders_blit_tag_glsl, "shaders/blit_tag.glsl", DATA_shaders_blit_tag_glsl, false)

static const unsigned char DATA_shaders_fog_glsl[772] __attribute__((aligned(4))) =
    "/* Stellarium Web Engine - Copyright (c) 2018 - Noctua Software Ltd\n"
    " *\n"
    " * This program is licensed under the terms of the GNU AGPL v3, or\n"
    " * alternatively under a commercial licence.\n"
    " *\n"
    " * The terms of the AGPL v3 license can be found in the main directory of this\n"
    " * repository.\n"
    " */\n"
    "\n"
    "#ifdef GL_ES\n"
    "precision mediump float;\n"
    "#endif\n"
    "\n"
    "varying lowp    vec4        v_color;\n"
    "\n"
    "#ifdef VERTEX_SHADER\n"
    "\n"
    "attribute highp   vec4       a_pos;\n"
    "attribute highp   vec3       a_sky_pos;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = a_pos;\n"
    "    const lowp float height = 0.2;\n"
    "    const lowp float alpha = 0.15;\n"
    "    lowp float d = smoothstep(height, 0.0, abs(a_sky_pos.z));\n"
    "    v_color = vec4(1.0, 1.0, 1.0, alpha * d);\n"
    "}\n"
    "\n"
    "#endif\n"
    "#ifdef FRAGMENT_SHADER\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = v_color;\n"
    "}\n"
    "\n"
    "#endif\n"
    "";

ASSET_REGISTER(shaders_fog_glsl, "shaders/fog.glsl", DATA_shaders_fog_glsl, false)

static const unsigned char DATA_shaders_lines_glsl[1217] __attribute__((aligned(4))) =
    "/* Stellarium Web Engine - Copyright (c) 2019 - Noctua Software Ltd\n"
    " *\n"
    " * This program is licensed under the terms of the GNU AGPL v3, or\n"
    " * alternatively under a commercial licence.\n"
    " *\n"
    " * The terms of the AGPL v3 license can be found in the main directory of this\n"
    " * repository.\n"
    " */\n"
    "\n"
    "uniform   lowp      vec2    u_win_size;\n"
    "uniform   lowp      float   u_line_width;\n"
    "uniform   lowp      float   u_line_glow;\n"
    "uniform   lowp      vec4    u_color;\n"
    "\n"
    "varying   mediump   vec2    v_uv;\n"
    "\n"
    "#ifdef VERTEX_SHADER\n"
    "\n"
    "attribute highp     vec2    a_pos;\n"
    "attribute highp     vec2    a_tex_pos;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4((a_pos / u_win_size - 0.5) * vec2(2.0, -2.0), 0.0, 1.0);\n"
    "    v_uv = a_tex_pos;\n"
    "}\n"
    "\n"
    "#endif\n"
    "#ifdef FRAGMENT_SHADER\n"
    "\n"
    "void main()\n"
    "{\n"
    "    mediump float dist = abs(v_uv.y); // Distance to line in pixel.\n"
    "    // Use smooth step on 2.4px to emulate an anti-aliased line\n"
    "    mediump float base = 1.0 - smoothstep(u_line_width / 2 - 1.2, u_line_width / 2 + 1.2, dist);\n"
    "    // Generate a glow with 5px radius\n"
    "    mediump float glow = (1.0 - dist / 5.0) * u_line_glow;\n"
    "    // Only use the most visible of both to avoid changing brightness\n"
    "    gl_FragColor = vec4(u_color.rgb, u_color.a * max(glow, base));\n"
    "}\n"
    "\n"
    "#endif\n"
    "";

ASSET_REGISTER(shaders_lines_glsl, "shaders/lines.glsl", DATA_shaders_lines_glsl, false)

static const unsigned char DATA_shaders_planet_glsl[7280] __attribute__((aligned(4))) =
    "/* Stellarium Web Engine - Copyright (c) 2018 - Noctua Software Ltd\n"
    " *\n"
    " * This program is licensed under the terms of the GNU AGPL v3, or\n"
    " * alternatively under a commercial licence.\n"
    " *\n"
    " * The terms of the AGPL v3 license can be found in the main directory of this\n"
    " * repository.\n"
    " */\n"
    "\n"
    "#define PI 3.14159265\n"
    "\n"
    "#ifdef GL_ES\n"
    "precision mediump float;\n"
    "#endif\n"
    "\n"
    "uniform lowp    vec4      u_color;\n"
    "uniform lowp    vec2      u_depth_range;\n"
    "uniform mediump sampler2D u_tex;\n"
    "uniform mediump sampler2D u_normal_tex;\n"
    "uniform mediump mat3      u_tex_transf;\n"
    "uniform mediump mat3      u_normal_tex_transf;\n"
    "uniform lowp    vec3      u_light_emit;\n"
    "uniform mediump mat4      u_mv;  // Model view matrix.\n"
    "uniform lowp    int       u_has_normal_tex;\n"
    "uniform lowp    int       u_material; // 0: Oren Nayar, 1: generic, 2: ring\n"
    "uniform lowp    int       u_is_moon; // Set to 1 for the Moon only.\n"
    "uniform lowp    float     u_contrast;\n"
    "\n"
    "uniform highp   vec4      u_sun; // Sun pos (xyz) and radius (w).\n"
    "\n"
    "#ifdef HAS_SHADOW\n"
    "// Up to four spheres for illumination ray tracing.\n"
    "uniform mediump sampler2D u_shadow_color_tex; // Used for the Moon.\n"
    "uniform lowp    int       u_shadow_spheres_nb;\n"
    "uniform highp   mat4      u_shadow_spheres;\n"
    "#endif\n"
    "\n"
    "varying highp   vec3 v_mpos;\n"
    "varying mediump vec2 v_tex_pos;\n"
    "varying mediump vec2 v_normal_tex_pos;\n"
    "varying lowp    vec4 v_color;\n"
    "varying highp   vec3 v_normal;\n"
    "varying highp   vec3 v_tangent;\n"
    "varying highp   vec3 v_bitangent;\n"
    "\n"
    "#ifdef VERTEX_SHADER\n"
    "\n"
    "attribute highp   vec4 a_pos;     // Projected position (with fake scaling).\n"
    "attribute highp   vec4 a_mpos;    // Model position (without fake scaling).\n"
    "attribute mediump vec2 a_tex_pos;\n"
    "attribute lowp    vec3 a_color;\n"
    "attribute highp   vec3 a_normal;\n"
    "attribute highp   vec3 a_tangent;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = a_pos;\n"
    "    gl_Position.z = (gl_Position.z - u_depth_range[0]) /\n"
    "                    (u_depth_range[1] - u_depth_range[0]);\n"
    "    v_mpos = a_mpos.xyz;\n"
    "    v_tex_pos = (u_tex_transf * vec3(a_tex_pos, 1.0)).xy;\n"
    "    v_normal_tex_pos = (u_normal_tex_transf * vec3(a_tex_pos, 1.0)).xy;\n"
    "    v_color = vec4(a_color, 1.0) * u_color;\n"
    "\n"
    "    v_normal = normalize(a_normal);\n"
    "    v_tangent = normalize(a_tangent);\n"
    "    v_bitangent = normalize(cross(v_normal, v_tangent));\n"
    "}\n"
    "\n"
    "#endif\n"
    "#ifdef FRAGMENT_SHADER\n"
    "\n"
    "float oren_nayar_diffuse(\n"
    "        vec3 lightDirection,\n"
    "        vec3 viewDirection,\n"
    "        vec3 surfaceNormal,\n"
    "        float roughness,\n"
    "        float albedo) {\n"
    "\n"
    "    float r2 = roughness * roughness;\n"
    "    float LdotV = dot(lightDirection, viewDirection);\n"
    "    float NdotL = dot(lightDirection, surfaceNormal);\n"
    "    float NdotV = dot(surfaceNormal, viewDirection);\n"
    "    float NaL = acos(NdotL);\n"
    "    float NaV = acos(NdotV);\n"
    "    float alpha = max(NaV, NaL);\n"
    "    float beta = min(NaV, NaL);\n"
    "    float gamma = dot(viewDirection - surfaceNormal * NdotV,\n"
    "                      lightDirection - surfaceNormal * NdotL);\n"
    "    float A = 1.0 - 0.5 * (r2 / (r2 + 0.33));\n"
    "    float B = 0.45 * r2 / (r2 + 0.09);\n"
    "    float C = sin(alpha) * tan(beta);\n"
    "    float scale = 1.6; // Empirical value!\n"
    "    return max(0.0, NdotL) * (A + B * max(0.0, gamma) * C) * scale;\n"
    "}\n"
    "\n"
    "/*\n"
    " * Compute the illumination if we only consider a single sphere in the scene.\n"
    " * Parameters:\n"
    " *   p       - The surface point where we compute the illumination.\n"
    " *   sphere  - A sphere: xyz -> pos, w -> radius.\n"
    " *   sun_pos - Position of the sun.\n"
    " *   sun_r   - Precomputed sun angular radius from the given point.\n"
    " */\n"
    "float illumination_sphere(highp vec3 p, highp vec4 sphere,\n"
    "                          highp vec3 sun_pos, highp float sun_r)\n"
    "{\n"
    "    // Sphere angular radius as viewed from the point.\n"
    "    highp float sph_r = asin(sphere.w / length(sphere.xyz - p));\n"
    "    // Angle <sun, pos, sphere>\n"
    "    highp float d = acos(min(1.0, dot(normalize(sun_pos - p),\n"
    "                                normalize(sphere.xyz - p))));\n"
    "\n"
    "    // Special case for the moon, to simulate lunar eclipses.\n"
    "    // We assume the only body that can cast shadow on the moon is the Earth.\n"
    "    if (u_is_moon == 1) {\n"
    "        if (d >= sun_r + sph_r) return 1.0; // Outside of shadow.\n"
    "        if (d <= sph_r - sun_r) return d / (sph_r - sun_r) * 0.6; // Umbra.\n"
    "        if (d <= sun_r - sph_r) // Penumbra completely inside.\n"
    "            return 1.0 - sph_r * sph_r / (sun_r * sun_r);\n"
    "        return ((d - abs(sun_r - sph_r)) /\n"
    "                (sun_r + sph_r - abs(sun_r - sph_r))) * 0.4 + 0.6;\n"
    "    }\n"
    "\n"
    "    if (d >= sun_r + sph_r) return 1.0; // Outside of shadow.\n"
    "    if (d <= sph_r - sun_r) return 0.0; // Umbra.\n"
    "    if (d <= sun_r - sph_r) // Penumbra completely inside.\n"
    "        return 1.0 - sph_r * sph_r / (sun_r * sun_r);\n"
    "\n"
    "    // Penumbra partially inside.\n"
    "    // I took this from Stellarium, even though I am not sure how it works.\n"
    "    highp float x = (sun_r * sun_r + d * d - sph_r * sph_r) / (2.0 * d);\n"
    "    highp float alpha = acos(x / sun_r);\n"
    "    highp float beta = acos((d - x) / sph_r);\n"
    "    highp float AR = sun_r * sun_r * (alpha - 0.5 * sin(2.0 * alpha));\n"
    "    highp float Ar = sph_r * sph_r * (beta - 0.5 * sin(2.0 * beta));\n"
    "    highp float AS = sun_r * sun_r * 2.0 * 1.57079633;\n"
    "    return 1.0 - (AR + Ar) / AS;\n"
    "}\n"
    "\n"
    "/*\n"
    " * Compute the illumination at a given point.\n"
    " * Parameters:\n"
    " *   p       - The surface point where we compute the illumination.\n"
    " */\n"
    "float illumination(vec3 p)\n"
    "{\n"
    "#ifndef HAS_SHADOW\n"
    "    return 1.0;\n"
    "#else\n"
    "    if (u_shadow_spheres_nb == 0) return 1.0;\n"
    "    mediump float ret = 1.0;\n"
    "    highp float sun_r = asin(u_sun.w / length(u_sun.xyz - p));\n"
    "    for (int i = 0; i < 4; ++i) {\n"
    "        if (u_shadow_spheres_nb > i) {\n"
    "            highp vec4 sphere = u_shadow_spheres[i];\n"
    "            ret = min(ret, illumination_sphere(p, sphere, u_sun.xyz, sun_r));\n"
    "        }\n"
    "    }\n"
    "    return ret;\n"
    "#endif\n"
    "}\n"
    "\n"
    "void main()\n"
    "{\n"
    "    vec3 light_dir = normalize(u_sun.xyz - v_mpos);\n"
    "    // Compute N in view space\n"
    "    vec3 n = v_normal;\n"
    "    if (u_has_normal_tex != 0) {\n"
    "        n = texture2D(u_normal_tex, v_normal_tex_pos).rgb - vec3(0.5, 0.5, 0.0);\n"
    "        // XXX: inverse the Y coordinates, don't know why!\n"
    "        n = +n.x * v_tangent - n.y * v_bitangent + n.z * v_normal;\n"
    "    }\n"
    "    n = normalize(n);\n"
    "    gl_FragColor = texture2D(u_tex, v_tex_pos) * v_color;\n"
    "    gl_FragColor.rgb = (gl_FragColor.rgb - 0.5) * u_contrast + 0.5;\n"
    "\n"
    "    if (u_material == 0) { // oren_nayar.\n"
    "        float power = oren_nayar_diffuse(light_dir,\n"
    "                                         normalize(-v_mpos),\n"
    "                                         n,\n"
    "                                         0.9, 0.12);\n"
    "        #ifdef HAS_SHADOW\n"
    "        lowp float illu = illumination(v_mpos);\n"
    "        power *= illu;\n"
    "        #endif\n"
    "\n"
    "        gl_FragColor.rgb *= power;\n"
    "\n"
    "        // Earth shadow effect on the moon.\n"
    "        #ifdef HAS_SHADOW\n"
    "        if (u_is_moon == 1 && illu < 0.99) {\n"
    "            vec4 shadow_col = texture2D(u_shadow_color_tex, vec2(illu, 0.5));\n"
    "            gl_FragColor.rgb = mix(\n"
    "                gl_FragColor.rgb, shadow_col.rgb, shadow_col.a);\n"
    "        }\n"
    "        #endif\n"
    "\n"
    "    } else if (u_material == 1) { // basic\n"
    "        vec3 light = vec3(0.0, 0.0, 0.0);\n"
    "        light += max(0.0, dot(n, light_dir));\n"
    "        light += u_light_emit;\n"
    "        gl_FragColor.rgb *= light;\n"
    "\n"
    "    } else if (u_material == 2) { // ring\n"
    "        lowp float illu = illumination(v_mpos);\n"
    "        gl_FragColor.rgb *= illu;\n"
    "    }\n"
    "}\n"
    "\n"
    "#endif\n"
    "";

ASSET_REGISTER(shaders_planet_glsl, "shaders/planet.glsl", DATA_shaders_planet_glsl, false)

static const unsigned char DATA_shaders_points_glsl[1039] __attribute__((aligned(4))) =
    "/* Stellarium Web Engine - Copyright (c) 2018 - Noctua Software Ltd\n"
    " *\n"
    " * This program is licensed under the terms of the GNU AGPL v3, or\n"
    " * alternatively under a commercial licence.\n"
    " *\n"
    " * The terms of the AGPL v3 license can be found in the main directory of this\n"
    " * repository.\n"
    " */\n"
    "\n"
    "uniform lowp vec4 u_color;\n"
    "uniform lowp float u_smooth;\n"
    "\n"
    "varying mediump vec2 v_tex_pos;\n"
    "varying lowp    vec4 v_color;\n"
    "\n"
    "#ifdef VERTEX_SHADER\n"
    "\n"
    "attribute highp   vec2  a_pos;\n"
    "attribute lowp    vec4  a_color;\n"
    "attribute mediump float a_size;\n"
    "\n"
    "void main()\n"
    "{\n"
    "    gl_Position = vec4(a_pos, 0, 1.0);\n"
    "    gl_PointSize = a_size;\n"
    "    v_color = a_color * u_color;\n"
    "}\n"
    "\n"
    "#endif\n"
    "#ifdef FRAGMENT_SHADER\n"
    "\n"
    "void main()\n"
    "{\n"
    "    mediump float dist;\n"
    "    mediump float k;\n"
    "\n"
    "    dist = 2.0 * distance(gl_PointCoord, vec2(0.5, 0.5));\n"
    "    k = smoothstep(1.0 - u_smooth, 1.0, dist);\n"
    "    k = sqrt(k);\n"
    "    gl_FragColor.rgb = v_color.rgb;\n"
    "    // Saturation effect at the center.\n"
    "    gl_FragColor.rgb *= 1.0 + smoothstep(0.2, 0.0, k);\n"
    "    gl_FragColor.a = v_color.a * (1.0 - k);\n"
    "}\n"
    "\n"
    "#endif\n"
    "";

ASSET_REGISTER(shaders_points_glsl, "shaders/points.glsl", DATA_shaders_points_glsl, false)

