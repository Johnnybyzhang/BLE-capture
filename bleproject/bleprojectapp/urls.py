from django.urls import path
from .views import JsonDataView

urlpatterns = [
    path('api/jsondata/', JsonDataView.as_view(), name='jsondata'),
]