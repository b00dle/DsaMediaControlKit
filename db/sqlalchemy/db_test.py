import db.base
from db.api import Api
from db.models import tables

def set_database_to_default(recreate=True):
    a = None
    if recreate:
        db.base.recreate_database()
        a = Api(bind=db.base.engine)
    else:
        a = Api(bind=db.base.engine)
        a._clear()
    a.close()
    del a
    a = None

if __name__ == "__main__":
	import random
	set_database_to_default(False)
	a = Api(bind=db.base.engine)
	a.open()

	rand_name = "foo"+str(random.randint(0,100000))+".mp3"

	s = tables.SoundFile()
	s.name = rand_name
	s.path = "path/to/" + rand_name
	s.relative_path = "to/" + rand_name
	
	c = tables.Category()
	c.name = "my first cat"

	sf_c = tables.SoundFileCategory()
	sf_c.sound_file = s
	sf_c.category = c
	
	a.insert_all([s,c,sf_c])
	
	if not a.commit():
		print "Failure: Could not add SoundFile."
	
	res = a.query(tables.SoundFileCategory)
	print res
	for row in res:
		print row.sound_file
		
	a.close()
	set_database_to_default()