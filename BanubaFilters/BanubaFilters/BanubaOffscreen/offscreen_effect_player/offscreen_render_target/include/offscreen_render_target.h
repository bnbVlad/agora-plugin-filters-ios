#pragma once

#include <bnb/types/base_types.hpp>

#include "offscreen_render_target_interface.hpp"

#include "program.hpp"

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreMedia/CoreMedia.h>
#import <OpenGLES/OpenGLESAvailability.h>
#import <OpenGLES/gltypes.h>
#import <OpenGLES/EAGL.h>

#include <mutex>

namespace bnb {
    class ort_frame_surface_handler;

    class offscreen_render_target : public interfaces::offscreen_render_target {
    public:
        offscreen_render_target(uint32_t width, uint32_t height);

        ~offscreen_render_target();

        void init() override;

        void deinit() override;

        void surface_changed(int32_t width, int32_t height) override;

        void activate_context() override;

        void deactivate_context() override;

        void prepare_rendering() override;

        void orient_image(interfaces::orient_format orient) override;

        bnb::data_t read_current_buffer() override;

        int get_current_buffer_texture() override;

    private:
        void create_context();

        void generate_texture(GLuint &texture);

        void prepare_post_processing_rendering();

        void delete_textures();

        uint32_t m_width;
        uint32_t m_height;

        GLuint m_framebuffer{0};
        GLuint m_post_processing_framebuffer{0};
        GLuint m_offscreen_render_texture{0};
        GLuint m_offscreen_post_processuing_render_texture{0};

        GLuint m_active_texture{0};

        EAGLContext *m_context;

        std::unique_ptr<program> m_program;
        std::unique_ptr<ort_frame_surface_handler> m_frame_surface_handler;

        std::once_flag m_init_flag;
        std::once_flag m_deinit_flag;
    };
} // bnb
