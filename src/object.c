//
// object.c
//

#include <stdlib.h>
#include <ncurses.h>
#include "world.h"
#include "object.h"
#include "display.h"

object * obj_new(obj_type type, chtype ch)
{
	object * o = malloc(sizeof(object));
	o->type = type;
	o->ch = ch;
	o->x = o->y = 0;
	o->z = NULL;
	return o;
}

void obj_free(object * o)
{
	free(o);
}

void obj_tele(object * obj, int x, int y, zone * z)
{
	if (z->objs[x][y] == NULL) {
		if (obj->z != NULL) {
			obj->z->objs[obj->x][obj->y] = NULL;
		}

		obj->x = x;
		obj->y = y;
		obj->z = z;

		z->objs[x][y] = obj;
	}
}

void obj_move(object * obj, int dx, int dy)
{
	int nx, ny;
	int ox = obj->x;
	int oy = obj->y;

	if (oy + dy >= 0 && oy + dy < obj->z->height
		&& ox + dx >= 0 &&ox + dx < obj->z->width)
	{
		obj->x = nx = ox + dx;
		obj->y = ny = oy + dy;

		obj->z->objs[ox][oy] = NULL;
		obj->z->objs[nx][ny] = obj;

		zone_update(obj->z, nx, ny);
		zone_update(obj->z, ox, oy);
		wrefresh(dispscr);
	}
}