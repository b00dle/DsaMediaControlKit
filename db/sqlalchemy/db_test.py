import db.base
from db.api import Api
from db.models import tables

def set_database_to_default(recreate=True):
    a = None
    if recreate:
        db.base.recreate_database()
        a = Api()
    else:
        a = Api()
        a._clear()
    a.close()
    del a
    a = None

if __name__ == "__main__":
	#set_database_to_default()
	a = Api()
	a.open()
	
	'''
	new_sf = tables.SoundFile()
	new_sf.name = "bar_file.mp3"
	new_sf.path = "path/to/bar_file.mp3"
	new_sf.relative_path = "to/bar_file.mp3"
	
	new_test = tables.Test()
	new_test.sound_file = new_sf	
	
	a.insert_all([new_sf, new_test])
	if a.commit():
		print "added sound_file and test... WOHOOO!"
		print " > SoundFile", new_sf
		print " > Test", new_test
	'''
	#test = a.select_test_by_id(1)
	#print "test record:", test
	#print "test > sound_file:", test.sound_file	
	
	res = a._db.query(tables.Test)
	print res.first()
	
	for row in res:
		print row.sound_file
	
	a.close()