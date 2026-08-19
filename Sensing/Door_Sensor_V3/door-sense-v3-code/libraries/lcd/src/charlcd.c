/* Character LCD Driver */

#include "libraries/lcd/charlcd.h"

static uint8_t rs = 0;
static uint8_t en = 0;
static uint8_t bl = 0;
static uint8_t d_4 = 0;
static uint8_t d_5 = 0;
static uint8_t d_6 = 0;
static uint8_t d_7 = 0;
static uint8_t cols = 0;
static uint8_t rows = 0;
static uint8_t display_control = 0;

void init_lcd(uint8_t regsel, uint8_t enable, uint8_t backl, uint8_t data4, uint8_t data5, uint8_t data6, uint8_t data7, uint8_t col, uint8_t row){
    /*
    Args:
        regsel (int):  Register select address GPIO pin.
        enable (int):  Enable GPIO pin.
        backl (int):   Enable backlight pin.
        data4 (int): Data4 GPIO pin.
        data5 (int): Data5 GPIO pin.
        data6 (int): Data6 GPIO pin.
        data7 (int): Data7 GPIO pin.
        cols (int): Number of character columns.
        rows (int): Number of display rows.
    */
    rs = regsel;
    en = enable;
    bl = backl;
    d_4 = data4;
    d_5 = data5;
    d_6 = data6;
    d_7 = data7;
    cols = col;
    rows = row;

    gpio_init(rs);
    gpio_init(en);
    gpio_init(bl);
    gpio_init(d_4);
    gpio_init(d_5);
    gpio_init(d_6);
    gpio_init(d_7);

    gpio_set_dir(rs, GPIO_OUT);
    gpio_set_dir(en, GPIO_OUT);
    gpio_set_dir(bl, GPIO_OUT);
    gpio_set_dir(d_4, GPIO_OUT);
    gpio_set_dir(d_5, GPIO_OUT);
    gpio_set_dir(d_6, GPIO_OUT);
    gpio_set_dir(d_7, GPIO_OUT);

    // Initialise display by sending bytes to LCD
    lcd_byte(0x33, LCD_CMD);
    lcd_byte(0x32, LCD_CMD);
    lcd_byte(0x28, LCD_CMD);
    lcd_byte(0x0C, LCD_CMD);
    lcd_byte(0x06, LCD_CMD);
    clear();

    display_control = (LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF);

    return;
}

void clear(void){
    // Clear and home LCD display
    lcd_byte(LCD_CLEAR, LCD_CMD);
    sleep_ms(HOMEDELAY);
    return;
}

void create_char(uint8_t location, uint8_t pattern[]){    
    /*
    Add custom character to LCD display.

    Args:
        location (int):  There are 8 CGRAM locations available (0 to 7).
        pattern ([byte]):  Byte array comprising custom character.
    Notes:
        There is an online tool to create custom characters:
        http://www.quinapalus.com/hd44780udg.html
        Character size should be 5x8.
        To show your custom character use hex address 0 to 7.
        example:  lcd.message('\x03')
    */

    // only position 0..7 are allowed
    if(location > 7){
        return;
    }

    lcd_byte(LCD_SETCGRAMADDR | (location << 3), LCD_CMD);

    for(uint8_t i; i < 8; i++){
        lcd_byte(pattern[i], LCD_CHR);
    }
    return;
}

void backlight(bool enable){
    /*
    Enable or disable backlight.
    Args:
        enable (bool):  True = On (default), False = Off
    */

    if(enable){
        gpio_put(bl, 1);
    }
    else{
        gpio_put(bl, 0);
    }
    return;
}

void enable(bool enable){
    /*
    Enable or disable display.
    Args:
        enable (bool):  True = On (default), False = Off
    */

    if(enable){
        display_control |= LCD_DISPLAYON;
    }
    else{
        display_control &= !LCD_DISPLAYON;
    }
    lcd_byte(LCD_DISPLAYCONTROL | display_control, LCD_CMD);
    return;
}

void home(void){
    // Return cursor to home position
    lcd_byte(LCD_HOME, LCD_CMD);
    sleep_ms(HOMEDELAY);
    return;
}

void lcd_byte(uint8_t bits, uint8_t mode){
    /*
    Send command or characters to LCD Display.

    Args:
        bits (byte):  Data to transmit to LCD Display.
        mode (LCD_CHR or LCD_CMD):  Specify character or command mode.
    */
    gpio_put(rs, mode);
    sleep_us(E_DELAY);

    // High bits
    gpio_put(d_4, 0);
    gpio_put(d_5, 0);
    gpio_put(d_6, 0);
    gpio_put(d_7, 0);
    if((bits & 0x10) == 0x10){
        gpio_put(d_4, 1);
    }
    if((bits & 0x20) == 0x20){
        gpio_put(d_5, 1);
    }
    if((bits & 0x40) == 0x40){
        gpio_put(d_6, 1);
    }
    if((bits & 0x80) == 0x80){
        gpio_put(d_7, 1);
    }

    // Toggle Enable pin.
    sleep_us(E_DELAY);
    gpio_put(en, 1);
    sleep_us(E_PULSE);
    gpio_put(en, 0);
    sleep_us(E_DELAY);

    // Low bits
    gpio_put(d_4, 0);
    gpio_put(d_5, 0);
    gpio_put(d_6, 0);
    gpio_put(d_7, 0);
    if((bits & 0x01) == 0x01){
        gpio_put(d_4, 1);
    }
    if((bits & 0x02) == 0x02){
        gpio_put(d_5, 1);
    }
    if((bits & 0x04) == 0x04){
        gpio_put(d_6, 1);
    }
    if((bits & 0x08) == 0x08){
        gpio_put(d_7, 1);
    }

    // Toggle Enable pin.
    sleep_us(E_DELAY);
    gpio_put(en, 1);
    sleep_us(E_PULSE);
    gpio_put(en, 0);
    sleep_us(E_DELAY);

    return;
}

void message(char message[]){
    /*
    Display text on LCD display.

    Args:
        message (string):  Text to display.
    */
    for(uint8_t i=0; i<strlen(message); i++){
        lcd_byte(message[i], LCD_CHR);
    }
    return;
}

void move_left(void){
    // Move display left one position.
    lcd_byte(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVELEFT, LCD_CMD);
    return;
}

void move_right(void){
    // Move display left one position.
    lcd_byte(LCD_CURSORSHIFT | LCD_DISPLAYMOVE | LCD_MOVERIGHT, LCD_CMD);
    return;
}

void set_cursor(uint8_t x, uint8_t y){
    /*
    Move the cursor to an explicit column and row position.

    Args:
        col (int):  Cursor column (zero is first column).
        row (int):  Cursor row (zero is first line).
    */

    // Clamp row to the last row of the display.
    if(y > rows){
        y = rows - 1;
    }
    // Set location.
    uint8_t row_offset = LCD_ROW_OFFSETS1;
    if(y == 1){
        row_offset = LCD_ROW_OFFSETS2;
    }
    else if(y == 2){
        row_offset = LCD_ROW_OFFSETS3;
    }
    else if(y == 3){
        row_offset = LCD_ROW_OFFSETS4; 
    }
    lcd_byte(LCD_SETDDRAMADDR | (x + row_offset), LCD_CMD);
    return;
}

void set_line(uint8_t num){
    /*
    Set cursor to specified line at column zero.

    Args:
        num (int):  Line number (zero based 0 - 3)
    */
    uint8_t line_val = LCD_LINES1;
    if(num == 1){
        line_val = LCD_LINES2;
    }
    else if(num == 2){
        line_val = LCD_LINES3;
    }
    else if(num == 3){
        line_val = LCD_LINES4;
    }
    else if(num > 3){
        return;
    }
    lcd_byte(line_val, LCD_CMD);
    return;
}


void show_blink(bool show){
    /*
    Enable or disable blinking cursor.

    Args:
        show (bool):  True = On (default), False = Off
    */

    if(show){
        display_control |= LCD_BLINKON;
    }
    else{
        display_control &= !LCD_BLINKON;
    }
    lcd_byte(LCD_DISPLAYCONTROL | display_control, LCD_CMD);
    return;
}

void show_underline(bool show){
    /*
    Enable or disable underline cursor.

    Args:
        blink (bool):  True = On (default), False = Off
    */

    if(show){
        display_control |= LCD_CURSORON;
    }
    else{
        display_control &= !LCD_CURSORON;
    }

    lcd_byte(LCD_DISPLAYCONTROL | display_control, LCD_CMD);

    return;
}
