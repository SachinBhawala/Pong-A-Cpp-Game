internal void 
clear_screen(u32 color) {
	unsigned int* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = color;
		}
	}
}

internal void 
draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 color) {
	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);


	for (int y = y0; y < y1; y++) {
		u32 * pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}
}

global_variable float render_scale = 0.01f;

internal void
draw_arena_borders(float arena_x, float arena_y, u32 color) {
    arena_x *= render_state.height * render_scale;
    arena_y *= render_state.height * render_scale;

    int x0 = (int)((float)render_state.width * .5f - arena_x);
    int x1 = (int)((float)render_state.width * .5f + arena_x);
    int y0 = (int)((float)render_state.height * .5f - arena_y);
    int y1 = (int)((float)render_state.height * .5f + arena_y);

    draw_rect_in_pixels(0, 0, render_state.width, y0, color);
    draw_rect_in_pixels(0, y1, x1, render_state.height, color);
    draw_rect_in_pixels(0, y0, x0, y1, color);
    draw_rect_in_pixels(x1, y0, render_state.width, render_state.height, color);
}

internal void
draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color) {
	x *= render_state.height * render_scale;
	y *= render_state.height * render_scale;
	half_size_x *= render_state.height * render_scale;
	half_size_y *= render_state.height * render_scale;


	x += render_state.width / 2.f;
	y += render_state.height / 2.f;

	// change to pixels
	int x0 = x - half_size_x;
	int x1 = x + half_size_x;
	int y0 = y - half_size_y;
	int y1 = y + half_size_y;

	draw_rect_in_pixels(x0, y0, x1, y1, color);
}

const char* letters[][7] = {
    // A
    " 00  ",
    "0  0 ",
    "0  0 ",
    "0000 ",
    "0  0 ",
    "0  0 ",
    "0  0 ",

    // B
    "000  ",
    "0  0 ",
    "0  0 ",
    "000  ",
    "0  0 ",
    "0  0 ",
    "000  ",

    // C
    " 000 ",
    "0    ",
    "0    ",
    "0    ",
    "0    ",
    "0    ",
    " 000 ",

    // D
    "000  ",
    "0  0 ",
    "0  0 ",
    "0  0 ",
    "0  0 ",
    "0  0 ",
    "000  ",

    // E
    "0000 ",
    "0    ",
    "0    ",
    "000  ",
    "0    ",
    "0    ",
    "0000 ",

    // F
    "0000 ",
    "0    ",
    "0    ",
    "000  ",
    "0    ",
    "0    ",
    "0    ",

    // G
    " 000 ",
    "0    ",
    "0    ",
    "0 00 ",
    "0  0 ",
    "0  0 ",
    " 000 ",

    // H
    "0  0 ",
    "0  0 ",
    "0  0 ",
    "0000 ",
    "0  0 ",
    "0  0 ",
    "0  0 ",

    // I
    " 000 ",
    "  0  ",
    "  0  ",
    "  0  ",
    "  0  ",
    "  0  ",
    " 000 ",

    // J
    "   00",
    "    0",
    "    0",
    "    0",
    "0   0",
    "0   0",
    " 000 ",

    // K
    "0  0 ",
    "0 0  ",
    "00   ",
    "0    ",
    "00   ",
    "0 0  ",
    "0  0 ",

    // L
    "0    ",
    "0    ",
    "0    ",
    "0    ",
    "0    ",
    "0    ",
    "0000 ",

    // M
    "0   0",
    "00 00",
    "0 0 0",
    "0   0",
    "0   0",
    "0   0",
    "0   0",

    // N
    "0   0",
    "00  0",
    "00  0",
    "0 0 0",
    "0  00",
    "0  00",
    "0   0",

    // O
    " 000 ",
    "0   0",
    "0   0",
    "0   0",
    "0   0",
    "0   0",
    " 000 ",

    // P
    "000  ",
    "0  0 ",
    "0  0 ",
    "000  ",
    "0    ",
    "0    ",
    "0    ",

    // Q
    " 000 ",
    "0   0",
    "0   0",
    "0   0",
    "0 0 0",
    "0  0 ",
    " 00 0",

    // R
    "000  ",
    "0  0 ",
    "0  0 ",
    "000  ",
    "0  0 ",
    "0  0 ",
    "0  0",

    // S
    " 0000",
    "0    ",
    "0    ",
    " 000 ",
    "    0",
    "    0",
    "0000 ",

    // T
    "00000",
    "  0  ",
    "  0  ",
    "  0  ",
    "  0  ",
    "  0  ",
    "  0  ",

    // U
    "0   0",
    "0   0",
    "0   0",
    "0   0",
    "0   0",
    "0   0",
    " 000 ",

    // V
    "0   0",
    "0   0",
    "0   0",
    "0   0",
    " 0 0 ",
    " 0 0 ",
    "  0  ",

    // W
    "0   0",
    "0   0",
    "0   0",
    "0   0",
    "0 0 0",
    "00 00",
    "0   0",

    // X
    "0   0",
    "0   0",
    " 0 0 ",
    "  0  ",
    " 0 0 ",
    "0   0",
    "0   0",

    // Y
    "0   0",
    "0   0",
    " 0 0 ",
    "  0  ",
    "  0  ",
    "  0  ",
    "  0  ",

    // Z
    "00000",
    "    0",
    "   0 ",
    "  0  ",
    " 0   ",
    "0    ",
    "00000",

    // :
    "     ",
    "  0  ",
    "  0  ",
    "     ",
    "  0  ",
    "  0  ",
    "     ",

    // Digit 1
    "  0  ",
    " 00  ",
    "  0  ",
    "  0  ",
    "  0  ",
    "  0  ",
    "00000",

    // Digit 2
    " 000 ",
    "0   0",
    "    0",
    "   0 ",
    "  0  ",
    " 0   ",
    "00000",

    // Upward Arrow
    "  0  ",
    " 000 ",
    "00000",
    "  0  ",
    "  0  ",
    "  0  ",
    "  0  ",

    // Dash (-)
    "     ",
    "     ",
    "     ",
    "00000",
    "     ",
    "     ",
    "     "
};

internal void
draw_text(const char *text, float x, float y, float size, u32 color) {
	float half_size = size * .5f;
	float original_y = y;

	while (*text) {
        if (*text != 32) {
            const char** letter;
            if (*text == 58) letter = letters[26];
            else if (*text == 49) letter = letters[27];
            else if (*text == 50) letter = letters[28];
            else if (*text == 48) letter = letters[29];
            else if (*text == 45) letter = letters[30];
            else letter = letters[*text - 'A'];
            float original_x = x;

            for (int i = 0; i < 7; i++) {
                const char* row = letter[i];
                while (*row) {
                    if (*row == '0') {
                        draw_rect(x, y, half_size, half_size, color);
                    }
                    x += size;
                    row++;
                }
                y -= size;
                x = original_x;
            }
        }
		text++;
		x += size * 6.f;
		y = original_y;
	}
}

internal void
draw_number(int number, float x, float y, float size, u32 color) {
	float half_size = size * .5f;

	bool drew_number = false;
	while(number || !drew_number) {
		drew_number = true;

		int digit = number % 10;
		number = number / 10;

		switch (digit) {
		case 0: {
			draw_rect(x - size, y, half_size, 2.5f * size, color);
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x, y + size * 2.f, half_size, half_size, color);
			draw_rect(x, y - size * 2.f, half_size, half_size, color);
			x -= size * 4.f;
		} break;

		case 1: {
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			x -= size * 2.f;
		} break;

		case 2: {
			draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x, y - size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x + size, y + size, half_size, half_size, color);
			draw_rect(x - size, y - size, half_size, half_size, color);
			x -= size * 4.f;
		} break;

		case 3: {
			draw_rect(x - half_size, y + size * 2.f, size, half_size, color);
			draw_rect(x - half_size, y, size, half_size, color);
			draw_rect(x - half_size, y - size * 2.f, size, half_size, color);
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			x -= size * 4.f;
		} break;

		case 4: {
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x - size, y + size, half_size, 1.5f * size, color);
			draw_rect(x, y, half_size, half_size, color);
			x -= size * 4.f;
		} break;

		case 5: {
			draw_rect(x, y + size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x, y, 1.5f * size, half_size, color);
			draw_rect(x, y - size * 2.f, 1.5f * size, half_size, color);
			draw_rect(x - size, y + size, half_size, half_size, color);
			draw_rect(x + size, y - size, half_size, half_size, color);
			x -= size * 4.f;
		} break;

		case 6: {
			draw_rect(x + half_size, y + size * 2.f, size, half_size, color);
			draw_rect(x + half_size, y, size, half_size, color);
			draw_rect(x + half_size, y - size * 2.f, size, half_size, color);
			draw_rect(x - size, y, half_size, 2.5f * size, color);
			draw_rect(x + size, y - size, half_size, half_size, color);
			x -= size * 4.f;
		} break;

		case 7: {
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x - half_size, y + size * 2.f, size, half_size, color);
			x -= size * 4.f;
		} break;

		case 8: {
			draw_rect(x - size, y, half_size, 2.5f * size, color);
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x, y + size * 2.f, half_size, half_size, color);
			draw_rect(x, y - size * 2.f, half_size, half_size, color);
			draw_rect(x, y, half_size, half_size, color);
			x -= size * 4.f;
		} break;

		case 9: {
			draw_rect(x - half_size, y + size * 2.f, size, half_size, color);
			draw_rect(x - half_size, y, size, half_size, color);
			draw_rect(x - half_size, y - size * 2.f, size, half_size, color);
			draw_rect(x + size, y, half_size, 2.5f * size, color);
			draw_rect(x - size, y + size, half_size, half_size, color);
			x -= size * 4.f;
		} break;
		}
	}
}