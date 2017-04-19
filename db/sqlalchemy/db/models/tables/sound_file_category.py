"""SoundFileCategory model"""
from db.base import TableBase
import db.constants

from sqlalchemy import Column, Integer, String
from sqlalchemy import ForeignKey
from sqlalchemy.orm import relationship
from sqlalchemy import Index

class SoundFileCategory(TableBase):
  """SoundFileCategory database object"""

  __tablename__ = 'sound_file_category'

  id = Column(Integer, primary_key=True)

  sound_file_id = Column(
    Integer, 
    ForeignKey("sound_file.id", onupdate=db.constants.CASCADE, ondelete=db.constants.CASCADE),
    nullable=False
  )
  
  category_id = Column(
    Integer, 
    ForeignKey("category.id", onupdate=db.constants.CASCADE, ondelete=db.constants.CASCADE),
    nullable=False
  )
  
  sound_file = relationship("SoundFile", uselist=False)
  category = relationship("Category", uselist=False)
  
  u_idx = Index(
    'sound_file_category_uidx',
    sound_file_id, category_id,
    unique=True
  )
  
  def __repr__(self):
    return "<SoundFileCategory id=%s sound_file_id=%s category_id=%s>" % (
        str(self.id), self.sound_file_id, self.category_id)
