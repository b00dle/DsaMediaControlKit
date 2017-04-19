"""ImageFileTag model"""
from db.base import TableBase
import db.constants

from sqlalchemy import Column, Integer, String
from sqlalchemy import ForeignKey
from sqlalchemy.orm import relationship
from sqlalchemy import Index

class ImageFileTag(TableBase):
  """ImageFileTag database object"""

  __tablename__ = 'image_file_tag'

  id = Column(Integer, primary_key=True)

  image_file_id = Column(
    Integer, 
    ForeignKey("image_file.id", onupdate=db.constants.CASCADE, ondelete=db.constants.CASCADE),
    nullable=False
  )
  
  tag_id = Column(
    Integer, 
    ForeignKey("tag.id", onupdate=db.constants.CASCADE, ondelete=db.constants.CASCADE),
    nullable=False
  )
  
  image_file = relationship("ImageFile", uselist=False)
  tag = relationship("Tag", uselist=False)
  
  u_idx = Index(
    'image_file_tag_uidx',
    image_file_id, tag_id,
    unique=True
  )
  
  def __repr__(self):
    return "<ImageFileTag id=%s image_file_id=%s tag_id=%s>" % (
        str(self.id), self.image_file_id, self.tag_id)
