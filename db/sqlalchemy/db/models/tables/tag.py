"""Tag model"""
from db.base import TableBase
import db.constants

from sqlalchemy import Column, Integer, String

class Tag(TableBase):
  """Tag database object"""

  __tablename__ = 'tag'

  id = Column(Integer, primary_key=True)

  name = Column(String(256), nullable=False, unique=True)
  
  def __repr__(self):
    return "<Tag id=%s name=%s>" % (
        str(self.id), self.name)
