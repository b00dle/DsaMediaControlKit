"""SoundFile model"""
from db.base import TableBase
import db.constants

from sqlalchemy import func
from sqlalchemy import Column, Integer, String
from sqlalchemy import ForeignKey
from sqlalchemy.orm import relationship

class SoundFile(TableBase):
  """SoundFile database object"""

  __tablename__ = 'sound_file'

  id = Column(Integer, primary_key=True)

  name = Column(String(256), nullable=False)
  
  path = Column(String(512), nullable=False, unique=True)
  
  relative_path = Column(String(512), nullable=False)
  
  '''
  resource_content_id = Column(
    Integer, 
    ForeignKey("resource_content.id", onupdate=db.constants.CASCADE, ondelete=db.constants.CASCADE),
    nullable=False
  )

  session = relationship("Session", uselist=False)
  user = relationship("RegisteredUser", uselist=False)
  resource_content = relationship("ResourceContent", uselist=False)
  '''
  
  def __repr__(self):
    return "<SoundFile id=%s name=%s path=%s relative_path=%s>" % (
        str(self.id), self.name, self.path, self.relative_path)
