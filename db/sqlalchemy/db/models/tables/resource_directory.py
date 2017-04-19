"""ResourceDirectory model"""
from db.base import TableBase
import db.constants

from sqlalchemy import Column, Integer, String

class ResourceDirectory(TableBase):
  """ResourceDirectory database object"""

  __tablename__ = 'resource_directory'

  id = Column(Integer, primary_key=True)

  name = Column(String(256))
  
  path = Column(String(512), unique=True)
  
  def __repr__(self):
    return "<ResourceDirectory id=%s name=%s path=%s>" % (
        str(self.id), self.name, self.path)
