"""Category model"""
from db.base import TableBase
import db.constants

from sqlalchemy import Column, Integer, String
from sqlalchemy import ForeignKey
from sqlalchemy.orm import relationship
from sqlalchemy import Index

class Category(TableBase):
  """Category database object"""

  __tablename__ = 'category'

  id = Column(Integer, primary_key=True)

  name = Column(String(256), nullable=False)

  parent_id = Column(
    Integer, 
    ForeignKey("category.id", onupdate=db.constants.CASCADE, ondelete=db.constants.CASCADE),
    nullable=True
  )
  
  parent = relationship("Category", uselist=False)
  
  u_idx = Index(
    'category_uidx',
    name, parent_id,
    unique=True
  )
  
  def __repr__(self):
    return "<Category id=%s name=%s parent_id=%s>" % (
        str(self.id), self.name, self.parent_id)
