void main()
{
	void par=getentityproperty(getlocalvar("self"),"parent");
	if(par)
	{
		void mp=getentityproperty(par,"mp");
		changeentityproperty(par,"mp",mp+10);
	}
	killentity(getlocalvar("self"));
}
