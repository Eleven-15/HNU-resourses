# labeltransfer.py

```python
import os
from os import getcwd

sets = ['train', 'val', 'test']
abs_path = os.getcwd()
print(abs_path)

wd = getcwd()
for image_set in sets:
    if not os.path.exists('data/labels/'):
        os.makedirs('data/labels/')
    image_ids = open('data/ImageSets/%s.txt' % (image_set)).read().strip().split('\n')
    list_file = open('data/%s.txt' % (image_set), 'w')
    for image_id in image_ids:
        list_file.write(abs_path + '/data/images/%s.jpg\n' % (image_id))
    list_file.close()
```
