recipes = [
    {
        'name': 'Tequila Sunrise',
        'index': 1,
        'ingredients': [
            {
                'ingredient': 'Tequila',
                'amount': 2,
            },
            {
                'ingredient': 'Orangensaft',
                'amount': 20,
            },
            {
                'ingredient': 'Grenadine',
                'amount': 1,
            }
        ]
    },
    {
        'name': 'Long Island Iced Tea',
        'index': 2,
        'ingredients': [
            {
                'ingredient': 'Tequila',
                'amount': 2,
            },
            {
                'ingredient': 'Wodka',
                'amount': 2,
            },
            {
                'ingredient': 'Gin',
                'amount': 2,
            },
            {
                'ingredient': 'Weisser Rum',
                'amount': 2,
            },
            {
                'ingredient': 'Triple Sec',
                'amount': 2,
            },
            {
                'ingredient': 'Zitronensaft',
                'amount': 2,
            },
            {
                'ingredient': 'Cola',
                'amount': 1,
            }
        ]
    }
]

bottles = [
    {
        'index': 1,
        'ingredient': 'Tequila'
    },
    {
        'index': 2,
        'ingredient': 'Orangensaft'
    },
    {
        'index': 3,
        'ingredient': 'Grenadine'
    },
    {
        'index': 4,
        'ingredient': 'Gin'
    },
    {
        'index': 5,
        'ingredient': 'Weisser Rum'
    },
    {
        'index': 6,
        'ingredient': 'Triple Sec'
    },
    {
        'index': 10,
        'ingredient': 'Triple Sec'
    },
    {
        'index': 7,
        'ingredient': 'Zitronensaft'
    },
    {
        'index': 8,
        'ingredient': 'Cola'
    },
    {
        'index': 9,
        'ingredient': 'Wodka'
    }
]


def tap_amount(amount):
    print("Zapfe %d cl." % amount)

def search_recipe(cocktail_index):
    found_recipe = None
    for recipe in recipes:
        if cocktail_index == recipe['index']:
            found_recipe = recipe
    return found_recipe

def make_cocktail(cocktail_index):
    found_recipe = search_recipe(cocktail_index)
    if found_recipe != None:
        cocktail_mixen(found_recipe)
    else:
        print("Leider ist der gewuenschte Cocktail nicht verfuegbar")

def select_bottle(index):
    for bottle in bottles:
        if index == bottle['index']:
            print("Flasche %d (%s) ausgewaehlt." % (index , bottle['ingredient']) )

def cocktail_mixen(recipe):
    print("Gerne mixe ich den %s" % recipe['name'])
    for ingredient in recipe['ingredients']:
        ingredient_name = ingredient['ingredient']
        for bottle in bottles:
            if bottle['ingredient'] == ingredient_name:
                select_bottle(bottle['index'])
                tap_amount(ingredient['amount'])
                break

for cocktail in recipes:
    print(str(cocktail['index']),cocktail['name' ])
make_cocktail(input("Welche Nummer hat dein Wunschcocktail?: "))



