/* An Erlang NIF WiringPi's LCD driver wrapper by Gordon Drogon:
   https://projects.drogon.net/raspberry-pi/wiringpi/lcd-library/

   Copyright 2012 Rafal Studnicki <studzien@gmail.com>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
  
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
  
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "erl_nif.h"
#include <wiringPi.h>
#include <lcd.h>

static int
load(ErlNifEnv* env, void** priv_data, ERL_NIF_TERM load_info)
{
    return wiringPiSetup(); // returns -1 in case of error ==> loading fails
}

static ERL_NIF_TERM
lcd_init(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  int rows, cols, bits, rs, strb, d0, d1, d2, d3, d4, d5, d6, d7;

  if (!enif_get_int(env, argv[0], &rows))
  {
    return enif_make_badarg(env);
  }
  if (!enif_get_int(env, argv[1], &cols))
  {
    return enif_make_badarg(env);
  } 
  if (!enif_get_int(env, argv[2], &bits))
  {
    return enif_make_badarg(env);
  }
  if (!enif_get_int(env, argv[3], &rs))
  {
    return enif_make_badarg(env);
  }
  if (!enif_get_int(env, argv[4], &strb))
  {
    return enif_make_badarg(env);
  }
  if (!enif_get_int(env, argv[5], &d0))
  {
    return enif_make_badarg(env);
  }
  if (!enif_get_int(env, argv[6], &d1))
  {
    return enif_make_badarg(env);
  } 
  if (!enif_get_int(env, argv[7], &d2))
  {
    return enif_make_badarg(env);
  }
  if (!enif_get_int(env, argv[8], &d3))
  {
    return enif_make_badarg(env);
  }
  if (!enif_get_int(env, argv[9], &d4))
  {
    return enif_make_badarg(env);
  }
  if (!enif_get_int(env, argv[10], &d5))
  {
    return enif_make_badarg(env);
  }
  if (!enif_get_int(env, argv[11], &d6))
  {
    return enif_make_badarg(env);
  }
  if (!enif_get_int(env, argv[12], &d7))
  {
    return enif_make_badarg(env);
  }

  int fd = lcdInit(rows, cols, bits, rs, strb, d0, d1, d2, d3, d4, d5, d6, d7);
  return enif_make_int(env, fd);
}

static ERL_NIF_TERM
lcd_home(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  int fd;
  if (!enif_get_int(env, argv[0], &fd)) {
    return enif_make_badarg(env);
  }

  lcdHome(fd);
  return enif_make_atom(env, "ok");
}

static ERL_NIF_TERM
lcd_clear(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  int fd;
  if (!enif_get_int(env, argv[0], &fd)) {
    return enif_make_badarg(env);
  }

  lcdClear(fd);
  return enif_make_atom(env, "ok");
}

static ERL_NIF_TERM
lcd_position(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  int fd, x, y;
  if (!enif_get_int(env, argv[0], &fd)) {
    return enif_make_badarg(env);
  }
  if (!enif_get_int(env, argv[1], &x)) {
    return enif_make_badarg(env);
  }
  if (!enif_get_int(env, argv[2], &y)) {
    return enif_make_badarg(env);
  }

  lcdPosition(fd, x, y);
  return enif_make_atom(env, "ok");
}

static ERL_NIF_TERM
lcd_putchar(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  int fd, data;
  if (!enif_get_int(env, argv[0], &fd)) {
    return enif_make_badarg(env);
  }
  if (!enif_get_int(env, argv[1], &data)) {
    return enif_make_badarg(env);
  }

  lcdPutchar(fd, data);
  return enif_make_atom(env, "ok");
}


static ERL_NIF_TERM
lcd_puts(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[])
{
  int fd;
  char string[256];
  if (!enif_get_int(env, argv[0], &fd)) {
    return enif_make_badarg(env);
  }
  if (!enif_get_string(env, argv[1], string, 256, ERL_NIF_LATIN1)) {
    return enif_make_badarg(env);
  }
  lcdPuts(fd, string);
  return enif_make_atom(env, "ok");
}

static ErlNifFunc nif_funcs[] =
    {
      {"lcd_init",  13, lcd_init},
      {"lcd_home",  1,  lcd_home},
      {"lcd_clear", 1,  lcd_clear},
      {"lcd_position",  3,  lcd_position},
      {"lcd_putchar", 2,  lcd_putchar},
      {"lcd_puts",  2,  lcd_puts}
    };

ERL_NIF_INIT(wpi_lcd, nif_funcs, load, NULL, NULL, NULL)
