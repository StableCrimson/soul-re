#ifndef _LOCALSTR_H_
#define _LOCALSTR_H_

typedef enum language_t {
    language_english = 0,
    language_french = 1,
    language_german = 2,
    language_italian = 3,
    language_spanish = 4,
    language_num_states = 5,
    //language_default    = 4294967295,
    language_default = 0xFFFFFFFF,
} language_t;

typedef enum localstr_t {
    LOCALSTR_BOGUS = 0,
    LOCALSTR_format_card = 1,
    LOCALSTR_accessing_card = 2,
    LOCALSTR_back = 3,
    LOCALSTR_cancel = 4,
    LOCALSTR_choose_load_file = 5,
    LOCALSTR_choose_save_file = 6,
    LOCALSTR_confirm = 7,
    LOCALSTR_continue = 8,
    LOCALSTR_controller = 9,
    LOCALSTR_create_file = 10,
    LOCALSTR_creating = 11,
    LOCALSTR_demos = 12,
    LOCALSTR_do_not_remove_card = 13,
    LOCALSTR_done = 14,
    LOCALSTR_exit_game = 15,
    LOCALSTR_formatting = 16,
    LOCALSTR_go_back = 17,
    LOCALSTR_insert_card = 18,
    LOCALSTR_insert_card_free = 19,
    LOCALSTR_invalid_card = 20,
    LOCALSTR_load_failed = 21,
    LOCALSTR_load_game = 22,
    LOCALSTR_loading = 23,
    LOCALSTR_music = 24,
    LOCALSTR_new_game = 25,
    LOCALSTR_no = 26,
    LOCALSTR_no_card = 27,
    LOCALSTR_card_full = 28,
    LOCALSTR_card_not_enough_blocks = 29,
    LOCALSTR_ok = 30,
    LOCALSTR_options = 31,
    LOCALSTR_overwrite_game = 32,
    LOCALSTR_paused = 33,
    LOCALSTR_press_start = 34,
    LOCALSTR_query_format_card = 35,
    LOCALSTR_query_overwrite = 36,
    LOCALSTR_query_quit = 37,
    LOCALSTR_quit_game = 38,
    LOCALSTR_resume_game = 39,
    LOCALSTR_save_failed = 40,
    LOCALSTR_save_game = 41,
    LOCALSTR_save_ok = 42,
    LOCALSTR_saving = 43,
    LOCALSTR_sound = 44,
    LOCALSTR_start_game = 45,
    LOCALSTR_start_new_game = 46,
    LOCALSTR_try_card_again = 47,
    LOCALSTR_unformatted_card = 48,
    LOCALSTR_vibration_off = 49,
    LOCALSTR_vibration_on = 50,
    LOCALSTR_voice = 51,
    LOCALSTR_warning_one = 52,
    LOCALSTR_warning_two = 53,
    LOCALSTR_yes = 54,
    LOCALSTR_Hint0 = 55,
    LOCALSTR_Hint1 = 56,
    LOCALSTR_Hint2 = 57,
    LOCALSTR_Hint3 = 58,
    LOCALSTR_Hint4 = 59,
    LOCALSTR_Hint5 = 60,
    LOCALSTR_Hint6 = 61,
    LOCALSTR_Hint7 = 62,
    LOCALSTR_Hint8 = 63,
    LOCALSTR_Hint9 = 64,
    LOCALSTR_Hint10 = 65,
    LOCALSTR_Hint11 = 66,
    LOCALSTR_Hint12 = 67,
    LOCALSTR_Hint13 = 68,
    LOCALSTR_Hint14 = 69,
    LOCALSTR_Hint15 = 70,
    LOCALSTR_Hint16 = 71,
    LOCALSTR_Hint17 = 72,
    LOCALSTR_Hint18 = 73,
    LOCALSTR_Hint19 = 74,
    LOCALSTR_Hint20 = 75,
    LOCALSTR_Hint21 = 76,
    LOCALSTR_Hint22 = 77,
    LOCALSTR_Hint23 = 78,
    LOCALSTR_Hint24 = 79,
    LOCALSTR_Hint25 = 80,
    LOCALSTR_Hint26 = 81,
    LOCALSTR_Hint27 = 82,
    LOCALSTR_Hint28 = 83,
    LOCALSTR_Hint29 = 84,
    LOCALSTR_Hint30 = 85,
    LOCALSTR_Hint31 = 86,
    LOCALSTR_Hint32 = 87,
    LOCALSTR_Hint33 = 88,
    LOCALSTR_Hint34 = 89,
    LOCALSTR_Hint35 = 90,
    LOCALSTR_Hint36 = 91,
    LOCALSTR_Hint37 = 92,
    LOCALSTR_Hint38 = 93,
    LOCALSTR_Hint39 = 94,
    LOCALSTR_Hint40 = 95,
    LOCALSTR_Hint41 = 96,
    LOCALSTR_Hint42 = 97,
    LOCALSTR_Hint43 = 98,
    LOCALSTR_Hint44 = 99,
    LOCALSTR_Hint45 = 100,
    LOCALSTR_Hint46 = 101,
    LOCALSTR_Hint47 = 102,
    LOCALSTR_Hint48 = 103,
    LOCALSTR_Hint49 = 104,
    LOCALSTR_Hint50 = 105,
    LOCALSTR_Hint51 = 106,
    LOCALSTR_Hint52 = 107,
    LOCALSTR_EndOfHintStrings = 108,
    LOCALSTR_no_controller = 109,
    LOCALSTR_NUM_ITEMS = 110,
} localstr_t;

#endif
