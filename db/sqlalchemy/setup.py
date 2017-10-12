import virtualenv
import pip
import os
import platform

# create virtual environment
print(" > creating virtualenv")
env_dir = os.path.dirname(os.path.realpath(__file__)) + '\\env'
print("   > path:" + env_dir)
virtualenv.create_environment(env_dir, clear=True)

# activate virtual environment
print(" > activating virtualenv from activation script")
activate_file = os.path.join(env_dir, "Scripts", "activate_this.py")
if platform.system() != 'Windows':
    activate_file = os.path.join(env_dir, "bin", "activate_this.py")
print("   > path:" + activate_file)
execfile(activate_file)

# install requirements from pip
print(" > installing pip requirements from file")
requirements_file = os.path.dirname(os.path.realpath(__file__)) + "\\requirements.txt"
print("   > path:" + requirements_file)
pip.main(["install", "--ignore-installed", "--prefix", env_dir, "-r", requirements_file])

# create database
import db.base
from db.models import tables
print(" > creating database")
db.base.recreate_database()