"""ImageFile model"""
from db.base import TableBase
import db.constants

from sqlalchemy import Column, Integer, String

class ImageFile(TableBase):
  """ImageFile database object"""

  __tablename__ = 'image_file'

  id = Column(Integer, primary_key=True)

  name = Column(String(256), nullable=False)
  
  relative_path = Column(
    String(512), 
    nullable=False,
    unique=True
  )
  
  def __repr__(self):
    return "<ImageFile id=%s name=%s relative_path=%s>" % (
        str(self.id), self.name, self.relative_path)
