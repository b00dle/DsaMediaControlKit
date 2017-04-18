"""Test model"""
from db.base import TableBase
import db.constants

from sqlalchemy import func
from sqlalchemy import Column, Integer
from sqlalchemy import ForeignKey
from sqlalchemy.orm import relationship

class Test(TableBase):
  """Test database object"""

  __tablename__ = 'test'

  id = Column(Integer, primary_key=True)

  sound_file_id = Column(
    Integer, 
    ForeignKey("sound_file.id", onupdate=db.constants.CASCADE, ondelete=db.constants.CASCADE),
    nullable=False
  )
  
  sound_file = relationship("SoundFile", uselist=False)
  
  def __repr__(self):
    return "<Test id=%s sound_file_id=%s>" % (
        str(self.id), self.sound_file_id)
