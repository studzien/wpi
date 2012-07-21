%%  An Erlang NIF WiringPi's LCD driver wrapper by Gordon Drogon:
%%  https://projects.drogon.net/raspberry-pi/wiringpi/lcd-library/
%% 
%%  Copyright 2012 Rafal Studnicki <studzien@gmail.com>
%%         
%%  This program is free software: you can redistribute it and/or modify
%%  it under the terms of the GNU General Public License as published by
%%  the Free Software Foundation, either version 3 of the License, or
%%  (at your option) any later version.
%%                     
%%  This program is distributed in the hope that it will be useful,
%%  but WITHOUT ANY WARRANTY; without even the implied warranty of
%%  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
%%  GNU General Public License for more details.
%%                                 
%%  You should have received a copy of the GNU General Public License
%%  along with this program.  If not, see <http://www.gnu.org/licenses/>.

-include_lib("wpi/include/wpi.hrl").

-export([ lcd_init/13,
          lcd_home/1,
          lcd_clear/1,
          lcd_position/3,
          lcd_putchar/2,
          lcd_puts/2
        ]).

-define(nif_stub,
        erlang:nif_error({nif_not_loaded, module, ?MODULE, line, ?LINE})).

-on_load(on_load/0).

-type wpi_pin_number()    :: integer().
-type wpi_fd()            :: integer().

on_load() ->
    Path = case code:priv_dir(wpi) of
      {error, _} -> "priv";
      Else -> Else
    end,
    ok = erlang:load_nif(Path ++ "/wpi_lcd", 0).

-spec lcd_init(integer(), integer(), integer(), wpi_pin_number(), wpi_pin_number(),
    wpi_pin_number(), wpi_pin_number(), wpi_pin_number(), wpi_pin_number(), 
    wpi_pin_number(), wpi_pin_number(), wpi_pin_number(), wpi_pin_number()) -> wpi_fd().
lcd_init(_Rows, _Cols, _Bits, _RS, _StrB, _D0, _D1, _D2, _D3, _D4, _D5, _D6, _D7) ->
  ?nif_stub.

-spec lcd_home(wpi_fd()) -> ok.
lcd_home(_Fd) ->
  ?nif_stub.

-spec lcd_clear(wpi_fd()) -> ok.
lcd_clear(_Fd) ->
  ?nif_stub.

-spec lcd_position(wpi_fd(), integer(), integer()) -> ok.
lcd_position(_Fd, _X, _Y) ->
  ?nif_stub.

-spec lcd_putchar(wpi_fd(), integer()) -> ok.
lcd_putchar(_Fd, _Data) ->
  ?nif_stub.

-spec lcd_puts(wpi_fd(), list()) -> ok.
lcd_puts(_Fd, _String) ->
  ?nif_stub.
