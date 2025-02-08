# txt2json.py

```python
import os
import json

WIDTH = 1920
HEIGHT = 1080

path = 'D:/code/pyproject/opencvlearning/ultralytics-main/runs/detect/predict3/labels'
files = os.listdir(path)
files.sort(key=lambda x: int(x.split(".")[0].split("_")[1]))
with open('D:/code/pyproject/opencvlearning/Resources/data_test.json') as f:
    data = json.load(f)

clips = data['clips']
clips_uid = {}
temp = 0
for clip in clips:
    clips_uid[clip['clip_uid']] = temp
    temp += 1
# print(clips_uid)
types = {}
with open('E:/CVtask/classes_test.txt') as fr:
    contents = fr.read()
lines = contents.split("\n")
index = 0
frames = []
for line in lines:
    types[index] = line
    index += 1
for file in files:
    # print(file)
    f = open(path + '/' + file, 'r', encoding='utf-8')
    first_line = f.readline().rstrip()
    yolo_data = first_line.split()
    # print(yolo_data)
    uid = file.split('_')[0]
    frame = int(file.split('_')[1].split('.')[0])
    clip_index = clips_uid[uid]
    clip = clips[clip_index]
    obj_title = types[int(yolo_data[0])]
    # print(obj_title)
    annotations = clip['annotations']
    anno_index = 0
    for annotation in annotations:
        if annotation['object_title'] == obj_title:
            break
        else:
            anno_index += 1
    anno = annotations[anno_index]
    lt_track = anno['lt_track']
    new_dict = {}
    new_dict['frame_number'] = frame // 6
    new_dict['x'] = round(float(WIDTH) * float(yolo_data[1]) - 0.5 * float(WIDTH) * float(yolo_data[3]), 2)
    new_dict['y'] = round(float(HEIGHT) * float(yolo_data[2]) - 0.5 * float(HEIGHT) * float(yolo_data[4]), 2)
    new_dict['width'] = round(float(WIDTH) * float(yolo_data[3]), 2)
    new_dict['height'] = round(float(HEIGHT) * float(yolo_data[4]), 2)
    new_dict['interpolated'] = False
    new_dict['exported_clip_frame_number'] = frame
    lt_track.append(new_dict)

# clips = data['clips']
# for clip in clips:
#     annotations = clip['annotations']
#     for annotation in annotations:
#         new_track = {}
#         annotation['lt_track'] = []

with open('D:/code/pyproject/opencvlearning/Resources/data_test.json', 'w') as newjsf:
    json.dump(data, newjsf)
```
