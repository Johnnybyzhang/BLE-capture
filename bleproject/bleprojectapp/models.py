from django.db import models

class JsonData(models.Model):
    data = models.JSONField()
    created_at = models.DateTimeField(auto_now_add=True)