"""SoundFile model"""
from db.base import TableBase
import db.constants

from sqlalchemy import Column, Integer, String

class SoundFile(TableBase):
  """SoundFile database object"""

  __tablename__ = 'sound_file'

  id = Column(Integer, primary_key=True)

  name = Column(String(256), nullable=False)
  
  path = Column(String(512), nullable=False, unique=True)
  
  relative_path = Column(String(512), nullable=False)
  
  def __repr__(self):
    return "<SoundFile id=%s name=%s path=%s relative_path=%s>" % (
        str(self.id), self.name, self.path, self.relative_path)
