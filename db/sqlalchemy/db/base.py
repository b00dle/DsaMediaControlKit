from sqlalchemy import create_engine
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.ext.declarative import declared_attr
from sqlalchemy.orm import sessionmaker
from sqlalchemy import exc
from sqlalchemy import event

from config import dev

from datetime import datetime

##
#  sqlalchemy database instance created based on uri
##

engine = create_engine(dev.SQLALCHEMY_DATABASE_DEBUG_URI, echo=dev.SQLALCHEMY_ECHO)

num_connections = 0

verbose = False

##
# Session pool logging
##
@event.listens_for(engine.pool, 'checkin')
def receive_checkin(connection, connection_record):
	''' called when session returns to pool. '''
	global num_connections
	global verbose
	num_connections -= 1
	if verbose:
		print "SQLALCHEMY: Session returned to pool.\n > num sessions used:" + str(num_connections)

@event.listens_for(engine.pool, 'checkout')
def receive_checkout(connection, connection_record, connection_proxy):
	''' called when session retrieved from pool. '''
	global num_connections
	num_connections += 1
	if verbose:
		print "SQLALCHEMY: Session retrieved from pool.\n > num sessions used:" + str(num_connections)

##
# Session factory to gain access to database
##
Session = sessionmaker(bind = engine)

##
# Declarative base extension
# to make each derived class dict serializable.
##
class _TableExt(object):
	@declared_attr
	def __tablename__(cls):
		return cls.__name__.lower()

	def as_dict(self):
		''' Returns all object properties as dictionary. '''
		dict = {c.name: getattr(self, c.name) for c in self.__table__.columns}
		for key in dict:
			if isinstance(dict[key], datetime):
				dict[key] = dict[key].isoformat()
		return dict

	def from_dict(self, d):
		''' Sets the objects attributes from python dict.
			Returns success of operation. '''
		if not isinstance(d, dict):
			print "Failure: parameter has to be a dictionary."
			return False
		for key in d:
			if hasattr(self, key):
				setattr(self, key, d[key])
			else:
				print "Failure:", type(self), " does not have '", key, "' attribute."
				print " > Skipping dict argument..."
		return True

##
# Base class for all table objects
##
TableBase = declarative_base(cls=_TableExt)

##
# base class for errors produced by sqlalchemy
##
Error = exc.SQLAlchemyError

##
# Functions for creating and dropping the database
##
def create_database():
	''' Creates the database from scratch. '''
	global TableBase
	global engine
	TableBase.metadata.create_all(engine)

def drop_database():
	''' Drops all database contents.
		ALL DATABASE TABLES/INDEXES AND DATA WILL BE LOST!'''
	global TableBase
	global engine
	TableBase.metadata.drop_all(engine)

def recreate_database():
	''' drops database and creates it from scratch. 
		ALL DATA WILL BE LOST! '''
	drop_database()
	create_database()