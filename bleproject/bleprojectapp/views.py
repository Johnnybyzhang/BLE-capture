from django.http import JsonResponse
from django.views.decorators.csrf import csrf_exempt
from django.utils.decorators import method_decorator
from django.views import View
import json
from .models import JsonData

@method_decorator(csrf_exempt, name='dispatch')
class JsonDataView(View):
    def post(self, request, *args, **kwargs):
        try:
            data = json.loads(request.body)
            JsonData.objects.create(data=data)
            return JsonResponse({'status': 'success'}, status=200)
        except json.JSONDecodeError:
            return JsonResponse({'status': 'error', 'message': 'Invalid JSON'}, status=400)