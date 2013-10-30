#include "ntk.h"

typedef enum {
	open,
	dicht
} klepStatus;	//Daadwerkelijke "hardware technische" toestand

typedef enum {
	vatStart,
	vatStop,
	vatOpTemp,
	vatTijdOm,
	vatLeeg
} eventForVat;	//Mogelijke gebeurtenissen (events)
typedef enum {
	idle,
	opwarmen,
	reaktie,
	leegLopen
} vatStatus;	//Mogelijke toestanden (states)

struct vat{
	vatStatus status;
	klepStatus gasKlep, losKlep;
	int readyProducts,
		cancelledProducts,
		illegalEvents;

	task* vatController;	/*implementatie concurrent gedrag, aktief object*/
	mailBox mailForVat;	/*implementatie asynchroon uitvoeren van opdrachten*/
};
typedef struct vat vat;

void create_vat(vat* v);
void sendEvent_vat(vat* v,eventForVat e);