/********************************************************************************************************
*	Structure Declarations
********************************************************************************************************/
struct color
{
	float 	r;
	float	g;
	float	b;
	float	a;
};
typedef struct color Color4;
struct vector
{
	float	x;
	float	y;
	float	z;
};
typedef struct vector Point3D;
typedef struct vector Vector3D;
struct Asteroid
{
	Color4			color;
	Point3D			pos;
	Vector3D		dir;
	Vector3D		spd;
	int			lifespan;
	int			size;
	struct Asteroid *	next;
};

/********************************************************************************************************
*	Function Prototypes
********************************************************************************************************/
int asteroid_init(struct Asteroid *p);
int asteroid_add(struct Asteroid **head);
int asteroid_remove(struct Asteroid *p);
int asteroid_destroy(struct Asteroid **head);
int asteroid_update(struct Asteroid **head);




