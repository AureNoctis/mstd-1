#if !defined(MSTD_GFX_H)
#define MSTD_GFX_H

typedef enum GFXFlag GFXFlag;
enum GFXFlag {
    GFX_FLAG_INIT_SOFTWARE_RENDERER
};

typedef struct GFXContext GFXContext;
struct GFXContext {
    u8 is_initialized;
    OS_Handle instance;
    OS_Handle window;

    enum_t(GFXFlag, u32) init_flags;
};


function void gfx_init(GFXContext* ctx, GFXFlag flags);
function void gfx_window_create(GFXContext* ctx, Str8 name, u32 width, u32 height);
function void gfx_poll_events(GFXContext* ctx, u32 peek);

#endif // MSTD_GFX_H