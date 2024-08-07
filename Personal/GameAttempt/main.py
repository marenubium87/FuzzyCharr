import pygame

pygame.init()

window = pygame.display.set_mode((640, 480))
pygame.display.set_caption("Woot!")
clock = pygame.time.Clock()

x = 120
y = 120
running = True
diff = 8

while running:
    for event in pygame.event.get():

        if event.type == pygame.QUIT:
            running = False
            break
        elif event.type == pygame.KEYDOWN:
            if event.key == pygame.K_ESCAPE:
                running = False
                break
            elif event.key == pygame.K_RIGHT:
                x += diff
            elif event.key == pygame.K_LEFT:
                x -= diff
            elif event.key == pygame.K_DOWN:
                y += diff
            elif event.key == pygame.K_UP:
                y -= diff

    window.fill((0,0,0))
    pygame.draw.rect(window,(0,0,255), (x, y, 400, 240))

    pygame.display.update()
    clock.tick(60)

pygame.quit()