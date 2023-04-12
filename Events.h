#ifndef events_h_INCLUDED
#define events_h_INCLUDED

enum event {
  volume_up       = 0,
  volume_down     = 1,
  
  mode_aux        = 2,
  mode_radio      = 3,
  power           = 4,
  open_cd         = 5,
  mode_cd         = 6,
  mode_tape       = 7,
  
  pause_play      = 8,
  menu_ok         = 9,
  menu_up         = 10,
  menu_down       = 11,
  radio_fm_am     = 12,
  radio_freq_up   = 13,
  radio_freq_down = 14,
  none            = 404,
};

enum mode {
  tape    = 2,
  radio   = 3,
  cd      = 6,
  aux     = 7,
  idle    = 0
};

enum modulation {
  fm = 1,
  am = 2
};

#endif
