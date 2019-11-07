void main()
{// Blink effect script
	void self = getlocalvar("self"); //Get calling entity.
	changeentityproperty(self, "colourmap", 3);
	changeentityproperty(self, "maptime", 14 + openborvariant("elapsed_time"));
}